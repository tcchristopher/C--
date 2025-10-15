// A program that converts 0-4 from user input into the corresponding word in a string
#include <iostream>

int main()
{
    std::cout << "Please enter a number between (zero, one, two, three, four) as a word: \n";
    std::string user_number;
    std::cin >> user_number;
    if (user_number == "zero")
        std::cout << "Your number is: " << 0 << '\n';
    else if (user_number == "one")
        std::cout << "Your number is: " << 1 << '\n';
    else if (user_number == "two")
        std::cout << "Your number is: " << 2 << '\n';
    else if (user_number == "three")
        std::cout << "Your number is: " << 3 << '\n';
    else if (user_number == "four")
        std::cout << "Your number is: " << 4 << '\n';
    else
        std::cout << "Not a number I know!\n";
}
