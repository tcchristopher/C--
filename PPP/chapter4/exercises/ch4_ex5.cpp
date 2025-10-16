// This is a basic calculator with four functions built around a switch
#include <iostream>

int main()
{
    std::cout << "Please enter two 'double' numbers and a operator (+, -, *, /) in the following format followed by 'enter':\n";
    std::cout << "45.0 22.5 +\n";
    std::string operation;
    double num1 = 0;
    double num2 = 0;
    std::cin >> num1 >> num2 >> operation;
    if (operation == "+")
        std::cout << "The sum is: " << num1 + num2 << '\n';
    if (operation == "-")
        std::cout << "The difference is: " << num1 - num2 << '\n';
    if (operation == "*")
        std::cout << "The product is: " << num1 * num2 << '\n';
    if (operation == "/")
        std::cout << "The quotient is: " << num1 / num2 << '\n';
    return 0;
}