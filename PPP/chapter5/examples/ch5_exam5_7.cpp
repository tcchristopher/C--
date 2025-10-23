// Logic Errors
#include "std_lib_facilities.h"

// Fix the initialisation error of 0
constexpr double max_temp = -1000;
constexpr double min_temp = 1000;


int main()
{
    vector<double> temps;                       // temperature

    for (double temp; std::cin >> temp; )
        temps.push_back(temp);
    
    double sum = 0;
    double high_temp = max_temp;
    double low_temp = min_temp;

    for (double x : temps)
    {
        if (x > high_temp) high_temp = x;       // find high
        if (x < low_temp) low_temp = x;         // find low
        sum += x;                               // compute sum
    }

    std::cout << "High temperature: " << high_temp << '\n';
    std::cout << "Low temperature: " << low_temp << '\n';
    std::cout << "Average temperature: " << sum/temps.size() << '\n';
}