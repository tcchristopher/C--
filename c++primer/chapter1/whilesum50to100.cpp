#include <iostream>

int main()
{
    int sum = 0, val = 50;
    while (val <= 100)
    {
        sum += val;
        ++val;
    }
    std::cout << "The sum of values between 50 and 100 inclusive is " << sum << std::endl;
    return 0;
}