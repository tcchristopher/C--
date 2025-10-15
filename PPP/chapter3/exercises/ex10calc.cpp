// A basic program that takes an operation and two operands and outputs the result
#include <iostream>

int main()
{
    std::cout << "Please enter an operation and two operands in the following format followed by 'enter':\n";
    std::cout << "+ 45 22\n";
    std::string operation;
    double num1 = 0;
    double num2 = 0;
    std::cin >> operation >> num1 >> num2;
    if (operation == "+")
        std::cout << "The result is: " << num1 + num2 << '\n';
    if (operation == "-")
        std::cout << "The result is: " << num1 - num2 << '\n';
    if (operation == "*")
        std::cout << "The result is: " << num1 * num2 << '\n';
    if (operation == "/")
        std::cout << "The result is: " << num1 / num2 << '\n';
    return 0;
}