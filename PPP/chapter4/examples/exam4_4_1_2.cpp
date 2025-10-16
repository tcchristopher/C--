// A switch statement program to convert centimeters to inches and bacl
#include <iostream>

int main()
{
    constexpr double cm_per_inch = 2.54;    // number of centimeters in an inch
    double length = 1;                      // length in centimeters or an inch
    char unit = ' ';
    std::cout << "Please enter a length followed by a space then a unit (c or i):\n";
    std::cin >> length >> unit;
    switch(unit){
    case 'i':
        std::cout << length << "in == " << cm_per_inch*length << "cm\n";
        break;
    case 'c':
        std::cout << length << "in == " << length/cm_per_inch << "in\n";
        break;
    default:
        std::cout << "Sorry, I don't know a unit called " << unit << "\n";
        break;
    }
}