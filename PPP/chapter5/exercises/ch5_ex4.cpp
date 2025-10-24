// Program for Chapter 5, Exercise 4
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
    // c must be above absolute zero (-273.15 degrees C)
    if (c > -273.15){
        double k = c + 273.15; 
        return k;
    } else{
        error("Please input a temperature equal to or above absolute zero\n");
        return 2;
    }
}