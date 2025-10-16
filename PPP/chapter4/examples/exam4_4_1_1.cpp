// A currency conversrion program for four currencies to dollar, using prefixes
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
    if (curr == 'p')
        std::cout << "Dollar USD = $" << cash * pound << ".\n";
    else if (curr == 'e')
        std::cout << "Dollar USD = $" << cash * euro << ".\n"; 
    else if (curr == 'y')
        std::cout << "Dollar USD = $" << cash * yen << ".\n";
    else if (curr == 'r')
        std::cout << "Dollar USD = $" << cash * rand << ".\n";
    else{
        std::cout << "You have entered an invalid currency.\n";
        return main();                                              // return to the start of the program (is this recursion????)
    }
    return 0;
}