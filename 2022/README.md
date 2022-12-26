# Advent of Code 2022

- day 6,9 - Incorrectly initialized variables are quite dangerous and introduce very sneaky errors. Beware of them.
    - What bit me is `int x, y =0;` where only `y` got initialized and `x` is undefined.
- day 11 - For numbers module x, y, the result will still stand the same for number modulo (x*y) module x or y.
    - Essentially `n mod m` is same as `(n mod k*m) mod m`