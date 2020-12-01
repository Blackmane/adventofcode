# adventofcode2020

My solution to Advent of Code 2020
https://adventofcode.com/


## How to compile

Go to the corresponding day folder and run
``` bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build
```

## How to run

You need a input.txt file.
Then, from the day folder run

``` bash
./build/bin/DayXX input.txt 
```

Change DayXX with correponding day.