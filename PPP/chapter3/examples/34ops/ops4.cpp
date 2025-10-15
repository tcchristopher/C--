// Read and compare names
#include <iostream>

int main()
{
    std::cout << "Please enter two names\n";
    std::string first;
    std::string second;
    std::cin >> first >> second;            // read two strings
    if (first == second) std::cout << "that's the same name twice\n";
    if (first < second)
        std::cout << first << " is alphabetically before " << second << '\n';
    if (first>second)
        std::cout << first << " is alphabetically after " << second << '\n';
    return 0;
}