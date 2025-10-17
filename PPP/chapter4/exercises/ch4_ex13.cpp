// Prime Numbers via the Sieve of Eratosthenes
#include <iostream>
#include <vector>
#include <numeric>

int main()
{
    // Declare vector of size
    std::vector<int> range(100);

    // Initialise the vector with values
    std::iota(range.begin(), range.end(), 1);

    // Pop out 1
    range.erase(find(range.begin(), range.end(), 1));

    // Apply the methodology (take a number from a range, remove multiples of it as you go along)
    // Traverse the vector
    for (int i = 0; i < range.size(); ++i){
        for (int j = i + 1; j < range.size(); ++j){
            if (range[j]%range[i] == 0){
                range.erase(range.begin() + j);
                --j;
            }
        }
    }

    // Print remaining vector
    for (int i = 0; i < range.size(); ++i)
        std::cout << range[i] << "\n";
}