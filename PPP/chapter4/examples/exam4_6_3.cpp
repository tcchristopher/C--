// A program that reads an unknown number of values into a vector, growing it.
#include <iostream>
#include "std_lib_facilities.h"

int main()
{
    vector<double> temps;              // temperatures
    for (double temp; std::cin >> temp; )   // read into temp, true for a value read, else flase otherwise
        temps.push_back(temp);              // put temp into vector
    
    // compute mean temperature:
    double sum = 0;
    for (double x : temps)
        sum += x;
    std::cout << "Average temperature: " << sum/temps.size() << '\n';

    // compute median temperature
    sort(temps);                            // sort temperatures
    std::cout << "Median temperature: " << temps[temps.size()/2] << '\n';
}
