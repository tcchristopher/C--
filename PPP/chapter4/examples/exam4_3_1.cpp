// A program to express the idea of constants in C++
#include <iostream>

int main()
{
    constexpr double pi = 3.14159265359;    // a constant needs to be known at runtime, before any operations.
    // pi = 7;                              // error: assignment to constant
    int r = 1;
    double c = 2*pi*r;                      // OK: we read pi, we don't change it. 
    return 0;
}

// But what if we don't know the value at runtime?
// C++ offers const for use in that scenario

constexpr int max = 100;

void use(int n)
{
    constexpr int c1 = max + 7;             // OK: c1 is 107 and it itself is not being used in a operation
    const int c2 = n + 7;                   // OK: but don't try to change the value of c2
    // ...
    //c2 = 7;                                 // error: c2 is a const.
    
}