# adventofcode2020

My solution to Advent of Code 2020
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

