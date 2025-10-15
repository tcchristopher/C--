// A program that converts miles into kilometers
#include <iostream>

int main()
{
    std::cout << "Please enter the number of miles (value only) you want to convert to kilometers: \n";
    double miles = 0;
    std::cin >> miles;
    std::cout << "The number of kilometres is: " << miles * 1.609 << "km.\n";
    return 0;
}