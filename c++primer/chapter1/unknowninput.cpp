#include <iostream>

int main()
{
    int sum = 0, value = 0; //  we have to ensure that each variable is cleanly set to
                            //  as the code struggles to recognise seperate variables otherwise
                            //  read until end-of-file, calculating a running total of all values read
    while (std::cin >> value)
    {
        sum += value;   //  equivalent to sum = sum + value
    }
    std::cout << "Sum is: " << sum << std::endl;
    return 0;
}