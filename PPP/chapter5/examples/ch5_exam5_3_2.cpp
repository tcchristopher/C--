// Examples of type errors
#include <iostream>
#include <string>
#include <vector>

int area(int length, int width);

int main()
{
    // int x0 = arena(7,5);            // error: undeclared function
    // int x1 = area(7);               // error: wrong number of arguments
    // int x2 = area("seven", 2);      // error: 1st argument has wrong type
}

int area(int length, int width)
{
    int area = length*width;
    return area;
}