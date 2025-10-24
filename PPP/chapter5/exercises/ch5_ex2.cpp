// Program for Chapter 5, Exercise 2
#include "std_lib_facilities.h"

double ctok(double c);

int main()
{
    double c = 0;               // declare input variable
    std::cin >> c;              // retrieve temperature to input variable
    double k = ctok(c);         // convert temperature
    std::cout << k << '\n';     // print out temperature

}

double ctok(double c)           // converts Celsius to Kelvin
{
    double k = c + 273.15;
    return k;
}