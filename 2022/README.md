# Advent of Code 2022

# General
- day 6,9
    - Incorrectly initialized variables are quite dangerous and introduce very sneaky errors. Beware of them.
    - What bit me is `int x, y =0;` where only `y` got initialized and `x` is undefined.
- day 11 
    - For numbers module x, y, the result will still stand the same for number modulo (x*y) module x or y.
    - Essentially `n mod m` is same as `(n mod k*m) mod m`


# Cpp
- day 11
    - Polymorphism only works for references & pointers in cpp
        - Found this when compiler complained about catching an exception by value using the base type `std::exception`.
            - See: https://stackoverflow.com/questions/15188894/why-doesnt-polymorphism-work-without-pointers-references
        - Object slicing comes into play when Derived object is assigned to base object by value
            - See: https://stackoverflow.com/questions/274626/what-is-object-slicing/14461532#14461532
- day 12
    - Do not take reference of priority queue top if you'd like to re-use the object. It refers to the address of the object in the pq's internal data structure. A `push` operation could fill that address with a new object causing the reference to point to this new object now.
    - Initialize 2D boolean arrays too. Nothing left uninitialized to guaranteed to work the way it seems like it should.