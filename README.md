# adventofcode

My solution to Advent of Code
https://adventofcode.com/

## adventofcode.py script

All the operation are centralized by `adventofcode.py` script.

```bash
usage: adventofcode.py [-h] {common,init,build,run,all} ...

Advent of Code utility application

positional arguments:
  {common,init,build,run,all}
    common              run tests for common lib
    init                init the current day directory
    build               just build the current day
    run                 run the current day
    all                 run all the day of a year

optional arguments:
  -h, --help            show this help message and exit

```
You can print this help message with the command `adventofcode.py -h`.

## Generate a day

```
usage: adventofcode.py init [-h] [-o] YEAR DAY

positional arguments:
  YEAR             current year of the AoC, is a directory name
  DAY              current day of the AoC, is a directory name, subdirectory of YEAR

optional arguments:
  -h, --help       show this help message and exit
  -o, --overwrite  if files already exists, overwrite them
```

With this code `python3 adventofcode.py init 2021 day01` you can generate the 2021/day01 directory and init it from the template.

## How to run test and code

```
usage: adventofcode.py run [-h] [-t] [-e] [-b] YEAR DAY

positional arguments:
  YEAR             current year of the AoC, is a directory name
  DAY              current day of the AoC, is a directory name, subdirectory of YEAR

optional arguments:
  -h, --help       show this help message and exit
  -t, --test       run the tests of the current day
  -e, --timing     print execution time of the current day
  -b, --benchmark  print benchmark of the current day
```

You can run test with `-t` flag: `python3 adventofcode.py run -t 2021 day01`. This command run the solution too.
With `-e` flag it enable the timing and print time elapsed.
The `-b` flag without `-t` flag do nothing.

Is possible to build witout run the code with the command `adventofcode.py build 2021 day01`. Use the same flags of the `run` command.
```
usage: adventofcode.py build [-h] [-t] [-e] YEAR DAY

positional arguments:
  YEAR          current year of the AoC, is a directory name
  DAY           current day of the AoC, is a directory name, subdirectory of YEAR

optional arguments:
  -h, --help    show this help message and exit
  -t, --test    build the tests of the current day
  -e, --timing  enable execution time of the current day
```

## Test common lib

```
usage: adventofcode.py common [-h]

optional arguments:
  -h, --help  show this help message and exit
```

You can run test for the common lib using the command `python3 adventofcode.py common`.


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
