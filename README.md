# adventofcode

My solution to Advent of Code
https://adventofcode.com/

## adventofcode.py script

All the operation are centralized by `adventofcode.py` script.

```bash
usage: adventofcode.py [-h] [-i] [-b] [-t] YEAR DAY

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
```

## Generate a day

With this code `python3 adventofcode.py -i 2021 day01` you can generate the 2021/day01 directory and init it from the
template.

## How to run test and code

You can run test with `-t` flag: `python3 adventofcode.py -t 2021 day01`. This command run the solution too. You can add
the flag `-b` to build only without run the code.

## Informations

Tested on

```
Arch Linux x86_64, kernel 5.9.10-arch1-1 
cmake version 3.19.1
gcc version 10.2.0 (GCC) 
```

## What i've learn

[AoC 2020](2020/aoc_learn.md) (in Italian).
