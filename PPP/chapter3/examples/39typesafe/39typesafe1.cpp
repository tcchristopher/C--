// Safe conversion examples
#include <iostream>

int main()
{
    char c = 'x';
    int i1 = c;
    int i2 = 'x';
    // Both i1 and i2 get the value 120, which is the ASCII integer value of 'x'
    char c2 = i1;
    std::cout << c << ' ' << i1 << ' ' << c2 << '\n';

    // Mixing ints and doubles
    double d1 = -2.3;
    double d2 = d1 + 2;     // 2 is converted to 2.0 before adding
    if (d1 <0)              // 0 is converted to 0.0 before comparision
        std::cout << "d1 is negative\n";
    return 0;
}