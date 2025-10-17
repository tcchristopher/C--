// Prime number generator for a counter of primes
#include <iostream>
#include <vector>

int main()
{
    std::vector<int>primes = {2};
    int num_primes = 0;
    std::cout << "Please enter the number of primes you would like to calculate: \n";
    std::cin >> num_primes;

    int counter = 1;
    int i = 2;

    while (counter < num_primes){
        ++i;
        bool is_prime = true;
        for (int j = 0; j < primes.size(); ++j){
            if (i%primes[j] == 0){
                is_prime = false;
                break;
            }
        }
        if (is_prime){
            primes.push_back(i);
            ++counter;
        }
    }

    // Print remaining vector
    for (int i = 0; i < primes.size(); ++i)
        std::cout << primes[i] << "\n";
}