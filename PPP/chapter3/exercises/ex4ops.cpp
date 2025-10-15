// A program that stores two integers from the User and does maths operations to them
#include <iostream>

int main()
{
    std::cout << "Please enter two integer values followed by 'enter':\n";
    int val1 = 0;
    int val2 = 0;
    std::cin >> val1 >> val2;
    // Which is smaller and which is larger?
    if (val1 < val2)
        std::cout << "The smaller of these is " << val1 << " and the larger is " << val2 << ".\n";
    else if (val1 > val2)
        std::cout << "The smaller of these is " << val2 << " and the larger is " << val1 << ".\n";
    
    // Difference between the numbers
    std::cout   << "The difference between the first and second value is: " << val2-val1 
                << ", and the second and first value is: " << val1-val2 << ".\n";
    
    // Product
    std::cout << "The product of the numbers is: " << val1*val2 << ".\n";

    // Ratio (division)
    std::cout   << "The ratio of the first to the second value is: " << val1/val2 
                << " and the ratio of the second to the first value is: " << val2/val1 << ".\n";
}