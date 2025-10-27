// The first attempt at the Calculator program, continued! This will break as it doesn't have BODMAS/PEMDAS
#include <iostream>
#include "std_lib_facilities.h"

int main()
{
    std::cout << "Please enter expression (we can handle +, -, *, and /)\n";
    std::cout << "add an x to end expression (e.g., 1+2*3x): ";
    int lval = 0;
    int rval;
    std::cin >> lval;                           // read leftmost operand
    if (!std::cin) error("no first operand");
    for (char op; std::cin>>op; ){              // read operator and right-hand operand repeatedly
        if (op != 'x') std::cin >>rval;
        if (!std::cin) error("no second operand");
        switch(op){
        case '+':
            lval += rval;                       // add: lval = lval + rval
            break;
        case '-':
            lval -= rval;                       // subtract: lval = lval = rval
            break;
        case '*':
            lval *= rval;                       // multiply: lval = lval * rval
            break;
        case '/':
            lval /= rval;                       // divide: lval = lval / rval
            break;
        default:
            std::cout << "Result: " << lval << '\n';
            keep_window_open();
            return 0;
        }
    }
    error("bad expression");
}

