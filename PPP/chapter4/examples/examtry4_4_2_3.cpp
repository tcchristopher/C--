// A program to iterate a while lopp giving equivalent int values for alphabetical values using a for loop
#include <iostream>

int main()
{
    for(int i = 96; i <= 'z'; ++i)
        std::cout << char(i) << '\t' << i << '\n';

    for(int i = 65; i <= 'Z'; ++i)
        std::cout << char(i) << '\t' << i << '\n';
}