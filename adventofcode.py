#!/usr/bin/python

import argparse
import scripts.init
import subprocess

build_dir = 'build'


def init(args):
    # Init the directory
    scripts.init.fromCurrentDir(args.year, args.day)
    return


def common(args):
    # Build and run common lib tests
    CMAKE_RUN = ['cmake', '-S', '.', '-B', build_dir,
                 '-DCMAKE_BUILD_TYPE=Release', '-DENABLE_COMMON_TESTING=on']
    subprocess.check_call(CMAKE_RUN)

    # Build
    subprocess.check_call(['cmake', '--build', build_dir])
    print("All compiled.\n\n")

    # Run tests
    print("> RUN tests: common lib")
    subprocess.check_call(['./%s/common/bin/test_common' % (build_dir)])


def build(args):
    # Cmake
    CMAKE_RUN = ['cmake', '-S', '.', '-B', build_dir, '-DYEAR=%s' % args.year, '-DDAY=%s' % args.day,
                                '-DCMAKE_BUILD_TYPE=Release']
    if args.test:
        CMAKE_RUN.append('-DENABLE_TESTING=on')
    else:
        CMAKE_RUN.append('-DENABLE_TESTING=off')
    if args.timing:
        CMAKE_RUN.append('-DENABLE_PRINT_TIMING=on')
    else:
        CMAKE_RUN.append('-DENABLE_PRINT_TIMING=off')
    CMAKE_RUN.append('-DENABLE_COMMON_TESTING=off')
        
    subprocess.check_call(CMAKE_RUN)

    # Build
    subprocess.check_call(['cmake', '--build', build_dir])
    print("All compiled.\n\n")


def run(args):
    build(args)
    sub_path = '%s/%s' % (args.year, args.day)
    # Run test
    if args.test:
        print("> RUN tests: %s/%s" % (args.year, args.day))
        subprocess.check_call(['./%s/%s/bin/test_%s' %
                              (build_dir, sub_path, args.day)])

    # Run
    print("> RUN %s/%s" % (args.year, args.day))
    subprocess.check_call(
        ['./%s/%s/bin/%s' % (build_dir, sub_path, args.day), '%s/input.txt' % sub_path])


def all(args):
    print("TODO: not implemented yet")


def parse():
    parser = argparse.ArgumentParser(
        description='Advent of Code utility application')
    subparsers = parser.add_subparsers()

    # common command
    parser_common = subparsers.add_parser(
        'common', help='run tests for common lib')
    parser_common.set_defaults(func=common)

    # init command
    parser_init = subparsers.add_parser(
        'init', help='init the current day directory')
    parser_init.add_argument('year', metavar='YEAR', type=str,
                             help='current year of the AoC, is a directory name')
    parser_init.add_argument('day', metavar='DAY', type=str,
                             help='current day of the AoC, is a directory name, subdirectory of YEAR')
    parser_init.set_defaults(func=init)

    # build command
    parser_build = subparsers.add_parser(
        'build', help='just build the current day')
    parser_build.add_argument('year', metavar='YEAR', type=str,
                              help='current year of the AoC, is a directory name')
    parser_build.add_argument('day', metavar='DAY', type=str,
                              help='current day of the AoC, is a directory name, subdirectory of YEAR')
    parser_build.add_argument('-t', '--test', dest='test',
                              action='store_true', help='build the tests of the current day')
    parser_build.add_argument('-e', '--timing', dest='timing',
                              action='store_true', help='enable execution time of the current day')
    parser_build.set_defaults(func=build)

    # run command
    parser_run = subparsers.add_parser('run', help='run the current day')
    parser_run.add_argument('year', metavar='YEAR', type=str,
                            help='current year of the AoC, is a directory name')
    parser_run.add_argument('day', metavar='DAY', type=str,
                            help='current day of the AoC, is a directory name, subdirectory of YEAR')
    parser_run.add_argument('-t', '--test', dest='test',
                            action='store_true', help='run the tests of the current day')
    parser_run.add_argument('-e', '--timing', dest='timing',
                            action='store_true', help='print execution time of the current day')
    parser_run.set_defaults(func=run)

    # all command
    parser_all = subparsers.add_parser('all', help='run all the day of a year')
    parser_all.add_argument('year', metavar='YEAR', type=str,
                            help='current year of the AoC, is a directory name')
    parser_all.set_defaults(func=all)

    return parser.parse_args()


def main():
    args = parse()
    args.func(args)


if __name__ == "__main__":
    main()
