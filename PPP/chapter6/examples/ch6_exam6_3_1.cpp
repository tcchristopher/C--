// The first attempt at the Calculator program!
#include <iostream>
#include "std_lib_facilities.h"

int main()
{
    std::cout << "Please enter expression (we can handle + and -): ";
    int lval = 0;
    int rval;
    char op;
    int res;
    std::cin >> lval >> op >> rval;             // read something like 1 + 3

    if (op == '+')
        res = lval + rval;                      // addition
    else if (op == '-')
        res = lval - rval;                      // subtraction
    
    std::cout << "Result: " << res << '\n';
    keep_window_open();
    return 0;    
}

