// read first and second name
#include <iostream>

int main()
{
    std::cout << "Please enter your first and second names\n";
    std::string first;
    std::string second;
    std::cin >> first >> second;            // read two strings
    std::string name = first + ' ' + second; // concatenate strings
    std::cout << "Hello, "<< name << '\n';
    return 0;
}