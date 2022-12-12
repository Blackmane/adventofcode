# adventofcode

My solution to Advent of Code
https://adventofcode.com/

## adventofcode.py script

All the operation are centralized by `adventofcode.py` script.

```bash
usage: adventofcode.py [-h] [-i] [-b] [-t] [-e] [-C] YEAR DAY

Advent of Code utility application

positional arguments:
  YEAR                  current year of the AoC, is a directory name
  DAY                   current day of the AoC, is a directory name, subdirectory of YEAR

optional arguments:
  -h, --help            show this help message and exit
  -i, --init            init the current day directory
  -b, --build, --no-run
                        just build the current day
  -t, --test            run the tests of the current day
  -e, --timing          print execution time
  -C, --common          enable testing for common lib
```
You can print this help message with the command `adventofcode.py -h`.

## Generate a day

With this code `python3 adventofcode.py -i 2021 day01` you can generate the 2021/day01 directory and init it from the template.

## How to run test and code

You can run test with `-t` flag: `python3 adventofcode.py -t 2021 day01`. This command run the solution too.
You can add the flag `-b` to build only without run the code.

You can run test for the common lib too, using the flag `-C`. At this time, you must specify the day and the year. So the command is like `python3 adventofcode.py -C 2021 day01` and run the solution too.

## Informations

Tested on

```
Arch Linux x86_64, kernel 5.9.10-arch1-1 
cmake version 3.19.1
gcc version 10.2.0 (GCC) 
```

```
Ubuntu 20.04.5 LTS x86_64, kernel 5.15.0-56-generic
cmake version 3.16.3
gcc version 9.4.0 (GCC) 
```

## What i've learn

[AoC 2020](2020/aoc_learn.md) (in Italian).
