// Read name and age

#include <iostream>

int main()
{
    std::cout << "Please enter your first name, your surname, and your age in years\n";
    std::string first_name = "???";     // string variable ("???" means "don't know the name")
    std::string second_name = "???";
    // int age = 0;                        // integer variable (0 means "don't know the age")
    float age = 0;
    std::cin >> first_name >> second_name >> age;      // read a string followed by an integer
    std::cout << "Hello, " << first_name << " " << second_name 
    << " (age " << age << " years old, which is " << age * 12 << " months old.)\n";
    return 0;
}