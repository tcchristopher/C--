// Program for Chapter 5, Exercise 5
#include "std_lib_facilities.h"

double ctok(double c);
double ktoc(double k);

int main()
{
    double temp_number = 0;                 // declare input variable
    string temp_type = "";                  // declare input type
    std::cout << "Please enter the temperature followed by the unit (C or K) in the following format: 23 C, 300 K.\n";
    std::cin >> temp_number >> temp_type;   // retrieve temperature to input variable
    if (temp_type == "C" || temp_type == "c"){
        double k = ctok(temp_number);                                   // convert temperature
        std::cout << "Your temperature in Kelvin: " << k << " K\n";      // print out temperature
    }
    else if (temp_type == "K" || temp_type == "k"){
        double c = ktoc(temp_number);
        std::cout << "Your temperature in Celsius: " << c << " C\n";
    }
    else {
        std::cout << "Please input a valid temperature and unit (C or k)\n";
        return main();
    }
}

double ctok(double c)           // converts Celsius to Kelvin
{
    // c must be above absolute zero (-273.15 degrees C)
    if (c >= -273.15){
        double k = c + 273.15; 
        return k;
    } else{
        error("Please input a temperature equal to or above absolute zero\n");
        return 2;
    }
}

double ktoc(double k)
{
    // k must be above absolute zero (0 degrees K)
    if (k >= 0){
        double c = k - 273.15;
        return c;
    } else{
        error("Please input a temperature equal to or above absolute zero (0 K)\n");
        return 3;
    }
}