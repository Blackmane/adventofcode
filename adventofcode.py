#!/usr/bin/python

import argparse
import scripts.init
import subprocess

build_dir = 'build'


def parse():
    parser = argparse.ArgumentParser(description='Advent of Code utility application')

    parser.add_argument('year', metavar='YEAR', type=str, help='current year of the AoC, is a directory name')
    parser.add_argument('day', metavar='DAY', type=str,
                        help='current day of the AoC, is a directory name, subdirectory of YEAR')
    parser.add_argument('-i', '--init', dest='init', action='store_true', help='init the current day directory')
    parser.add_argument('-b', '--build', '--no-run', dest='no_run', action='store_true',
                        help='just build the current day')
    parser.add_argument('-t', '--test', dest='test', action='store_true', help='run the tests of the current day')
    parser.add_argument('-T', '--timing', dest='timing', action='store_true', help='print execution time')
    parser.add_argument('-C', '--common', dest='common', action='store_true', help='enable testing for common lib')

    return parser.parse_args()


def main():
    args = parse()
    # Init the directory
    if args.init:
        scripts.init.fromCurrentDir(args.year, args.day)
        return

    # Cmake
    CMAKE_RUN = ['cmake', '-S', '.', '-B', build_dir, '-DYEAR=%s' % args.year, '-DDAY=%s' % args.day, 
                                '-DCMAKE_BUILD_TYPE=Release']
    if args.test:
        CMAKE_RUN.append('-DENABLE_TESTING=on')
    if args.timing:
        CMAKE_RUN.append('-DPRINT_TIMING=on')
    if args.common:
        CMAKE_RUN.append('-DENABLE_COMMON_TESTING=on')
    
    subprocess.check_call(CMAKE_RUN)

    # Build
    subprocess.check_call(['cmake', '--build', build_dir])

    sub_path = '%s/%s' % (args.year, args.day)

    print("All compiled.\n\n")
    # Run common test
    if args.common:
        print("> RUN tests: common lib")
        subprocess.check_call(['./%s/common/bin/test_common' % (build_dir)])

    # Run test
    if args.test:
        print("> RUN tests: %s/%s" % (args.year, args.day))
        subprocess.check_call(['./%s/%s/bin/test_%s' % (build_dir, sub_path, args.day)])

    # Run
    if not args.no_run:
        print("> RUN %s/%s" % (args.year, args.day))
        subprocess.check_call(['./%s/%s/bin/%s' % (build_dir, sub_path, args.day), '%s/input.txt' % sub_path])


if __name__ == "__main__":
    main()
