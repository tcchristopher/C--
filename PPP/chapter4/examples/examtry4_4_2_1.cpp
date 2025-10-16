// A program to iterate a while lopp giving equivalent int values for alphabetical values
#include <iostream>

int main()
{
    int i = 0;      // Loop variable
    char alpha = 'a';
    
    while(i<=('z'-alpha)){
        std::cout << char(alpha + i) << '\t' << alpha + i << '\n';
        ++i;
    }
}