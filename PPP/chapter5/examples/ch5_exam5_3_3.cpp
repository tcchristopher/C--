// Examples of non-errors
#include <iostream>
#include <string>
#include <vector>

int area(int length, int width);

int main()
{
    int x4 = area(10, -7);              // OK: but what is a rectangle of -7 width and -70 area?
    int x5 = area(10.7, 9.3);           // OK: but calls area(10,9)
    char x6 = area(100, 9999);          // OK: but truncates the result
}

int area(int length, int width)
{
    int area = length*width;
    return area;
}