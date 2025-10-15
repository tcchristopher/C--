// Demonstrates an unsafe conversion
#include <iostream>

int main()
{
    int a = 20000;
    char c = a;         // try to squeeze a large int into a small char
    int b = c;
    if (a != b)
        std::cout << "oops!: " << a << " != " << b << '\n';
    else
        std::cout << "Wow! We have large characters!\n";
    return 0;
}