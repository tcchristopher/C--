// A currency conversrion program for four currencies to dollar, using prefixes and a SWITCH
#include <iostream>

int main()
{
    // As of 16 October 2025
    constexpr double pound = 1.34;
    constexpr double euro = 1.17;
    constexpr double yen = 0.0066;
    constexpr double rand = 0.058;

    double cash = 0.0;
    char curr = ' ';

    std::cout << "Please enter your cash currency, with a suffix of p for British Pound, e for Euro, y for Japanese Yen and r for South African Rand: \n";
    std::cin >> curr >> cash;
    switch(curr){
    case('p'):
        std::cout << "Dollar USD = $" << cash * pound << ".\n";
        break;
    case('e'):
        std::cout << "Dollar USD = $" << cash * euro << ".\n"; 
        break;
    case('y'):
        std::cout << "Dollar USD = $" << cash * yen << ".\n";
        break;
    case('r'):
        std::cout << "Dollar USD = $" << cash * rand << ".\n";
        break;
    default:
        std::cout << "You have entered an invalid currency.\n";
        break;                                           
    }
}