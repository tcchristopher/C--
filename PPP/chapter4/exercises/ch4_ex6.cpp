// A program that converts numbers to their spoken words and back again
#include <iostream>

int main()
{
    std::vector<std::string>words = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int number = 0;
    std::cout << "Please enter the number (int) between 0 and 10 you'd like to spell out: \n";
    while(std::cin >> number)
        std::cout << "Your number is " << words[number] << '\n';
}