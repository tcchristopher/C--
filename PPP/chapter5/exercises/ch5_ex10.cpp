// Sum Calculator for exercises 8, 9
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

double sum_of_series(int n, std::vector<double> series);

int main()
{
    // Initialise the storage vectors
    double sum = 0;
    int n = 0;
    std::vector<double>series;
    std::vector<double>diffs;
    double temp = 0;

    // Prompt for input from the user and store it (use infinite while)
    // First N
    std::cout << "Please enter the number of values you want to sum:\n";
    std::cin >> n;

    // Error message if not an int and not positive
    if (n <= 0)
    {
        std::cerr << "ERROR: Please enter a positive, non-zero number.\n";
        return 1;
    }

    // Then the series into the vector
    std::cout << "Please enter some doubles (press '|' to stop):\n";
    while (std::cin >> temp)
    {
        series.push_back(temp);
    }

    // Check to see that N <= vector.size()
    if (n > series.size()){
        std::cerr << "ERROR: The number of values you want to sum exceeds the total available integers entered. Try again.\n";
        return 1;
    }

    // Do the calculations
    sum = sum_of_series(n, series);
    std::cout << "The sum of the series is: " << sum << '\n';

    // Create a differences vector
    for (int i = 1; i < n; ++i){
        diffs.push_back(series[i] - series[i-1]);
    }

    // Write out the differences
    std::cout << "The differences vector is:";
    for (int i = 0; i < (n-1); ++i){
        std::cout << " " << diffs[i];
    }
    std::cout << '\n';
}

double sum_of_series(int n, std::vector<double> series)
{
    double series_sum = 0;

    // Sum with a for loop and N as the limit
    for (int i=0; i < n; ++i)
        series_sum += series[i];

    // Output the sum and return the value
    return series_sum;
}