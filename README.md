# adventofcode

My solution to Advent of Code
https://adventofcode.com/


## How to compile

Go to the corresponding day folder and run
``` bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build
```

## How to run

You need a input.txt file (not all days).
Then, from the day folder run

``` bash
./build/bin/dayXX input.txt 
```

Change dayXX with correponding day.


## Informations

Tested on 
```
Arch Linux x86_64, kernel 5.9.10-arch1-1 
cmake version 3.19.1
gcc version 10.2.0 (GCC) 
```

## How to use daygen

Daygen create a new directory NAME in PATH. Create NAME.cpp and CMakeLists, ready to start coding.

Run with
``` bash
python daygen.py PATH NAME
```
example
``` bash
python daygen.py 2015 day06

Create 2015/day06 ? (Y)
>y
continue
Create dir
Create: 2015/day06/day06.cpp
Create: 2015/day06/CMakeLists.txt
Create: 2015/day06/input.txt
done
```


## What i've learn

[AoC 2020](2020/aoc_learn.md) (in Italian).
