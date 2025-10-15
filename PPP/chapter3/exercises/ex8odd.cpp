// A program that tests if an integer is odd or even
#include <iostream>

int main()
{
    std::cout << "Please enter an integer value, followed by 'enter': \n";
    int test_value = 0;
    std::cin >> test_value;
    if (test_value % 2 == 0)
        std::cout << "The number " << test_value << " is even.\n";
    else
        std::cout << "The number " << test_value << " is odd.\n";
}