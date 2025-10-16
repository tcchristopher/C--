#include <iostream>

int main() {
    int num;
    std::cin >> num;
    
    std::cout << "Read: " << num << "\n";
    std::cout << "fail: " << std::cin.fail() << "\n";
    
    std::string rest;
    std::cin.clear();
    std::getline(std::cin, rest);
    std::cout << "Remaining: '" << rest << "'\n";
    
    return 0;
}