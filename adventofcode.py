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

    return parser.parse_args()


def main():

    args = parse()
    # Init the directory
    if args.init:
        scripts.init.fromCurrentDir(args.year, args.day)
        pass

    # TODO: if test build with test e run test

    # Build
    subprocess.check_call(['cmake', '-S', '.', '-B', build_dir, '-DYEAR=%s' % args.year, '-DDAY=%s' % args.day])
    subprocess.check_call(['cmake', '--build', build_dir])

    # Test
    if args.test:
        subprocess.check_call(['cmake', '--build', build_dir, '--target', 'test'])

    # Run
    if not args.no_run:
        subprocess.check_call(['./%s/%s/%s/bin/%s' % (build_dir, args.year, args.day, args.day)])


if __name__ == "__main__":
    main()