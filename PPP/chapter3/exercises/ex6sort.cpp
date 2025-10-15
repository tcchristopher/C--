// A program that sorts three integer numbers from the user
#include <iostream>

int main()
{
    std::cout << "Please enter three integer numbers, followed by 'enter': \n";
    int val1 = 0;
    int val2 = 0;
    int val3 = 0;
    std::cin >> val1 >> val2 >> val3;

    // Sorted by if statements
    if (val1 <= val2 && val1 <= val3){
        std::cout << val1 << ", ";
        if (val2 <= val3){
            std::cout << val2 << ", " << val3 << '\n';
        }
        else {
            std::cout << val3 << ", " << val2 << '\n';
        }
    }    
    else if (val2 <= val3 && val2 <= val1){
        std::cout << val2 << ", ";
        if (val1 <= val3){
            std::cout << val1 << ", " << val3 << '\n';
        }
        else {
            std::cout << val3 << ", " << val1 << '\n';
        }
    }
    else if (val3 <= val1 && val3 <= val2){
        std::cout << val3 << ", ";
        if (val1 <= val2) {
            std::cout << val1 << ", " << val2 << '\n';
        }
        else {
            std::cout << val2 << ", " << val1 << '\n';
        }
    }
    return 0;
}