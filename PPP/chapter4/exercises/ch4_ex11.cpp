// Prime number generator
#include <iostream>
#include <vector>

int main()
{
    std::vector<int>primes ={2};
    for (int i = 3; i <= 100; ++i){
        bool is_prime = true;
        for (int j = 0; j < primes.size(); ++j){
            if (i%primes[j] == 0){
                is_prime = false;
                break;
            }
        }
        if (is_prime){
            primes.push_back(i);
            std::cout << i << '\n';
        }
    }
}