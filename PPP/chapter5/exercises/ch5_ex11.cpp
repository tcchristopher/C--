// Fibonacci sequence up until the limit of a integer
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

int main()
{
    // Do the sequencing and arithmetic in long long, which is just above int, 
    // and break when the calculated number is larger than an INT_MAX
    std::vector<long long>fibo = {1, 1};
    long long temp = 0;

    while (true){
        temp = fibo[fibo.size()-2] + fibo[fibo.size()-1];
        if (temp > INT_MAX)
            break;
        std::cout << temp << '\n';
        fibo.push_back(temp);
    }
    std::cout << "The largest Fibonacci number in an int is: " << fibo[fibo.size()-1] << '\n';
}