// Convert temperature between Fahrenheit and Celsius
// Program for Chapter 5, Exercise 6
#include "std_lib_facilities.h"

double ctof(double c);
double ftoc(double f);

int main()
{
    double temp_number = 0;                 // declare input variable
    string temp_type = "";                  // declare input type
    std::cout << "Please enter the temperature followed by the unit (C or F) in the following format: 23 C, 86 F.\n";
    std::cin >> temp_number >> temp_type;   // retrieve temperature to input variable
    if (temp_type == "C" || temp_type == "c"){
        double f = ctof(temp_number);                                   // convert temperature
        std::cout << "Your temperature in Fahrenheit: " << f << " F\n";      // print out temperature
    }
    else if (temp_type == "F" || temp_type == "f"){
        double c = ftoc(temp_number);
        std::cout << "Your temperature in Celsius: " << c << " C\n";
    }
    else {
        std::cout << "Please input a valid temperature and unit (C or F)\n";
        return main();
    }
}

double ctof(double c)           // converts Celsius to Fahrenheit
{
    // c must be above absolute zero (-273.15 degrees C)
    if (c >= -273.15){
        double f = (c*(1.8)) + 32; 
        return f;
    } else{
        error("Please input a temperature equal to or above absolute zero\n");
        return 2;
    }
}

double ftoc(double f)           // converts Fahrenheit to Celsius
{
    // f must be above absolute zero (-459.67 degrees F)
    if (f >= 0){
        double c = (f - 32)/(1.8);
        return c;
    } else{
        error("Please input a temperature equal to or above absolute zero (-459.67 F)\n");
        return 3;
    }
}