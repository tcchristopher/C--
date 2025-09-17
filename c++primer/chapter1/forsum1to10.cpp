#include <iostream>

int main()
{
    int sum = 0;

    //  Using a for statement to get the counting loop needed
    for (int i = 1; i <= 10; ++i)
    {
        sum += i;
    }
    std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;
    return 0;
}