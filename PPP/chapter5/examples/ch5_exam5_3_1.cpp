// Examples of compile-time errors
#include <iostream>
#include <string>
#include <vector>

int area(int length, int width);

int main()
{
    // int s1 = area(7, 5;         // error: ) missing
    // int s2 = area(7, 5)         // error: ; missing
    // Int s3 = area (7, 5);       // error: Int is not a type
    // int s3 = area('7, 5);       // error: non-terminated character (' missing)

    int s1 = area(7, 5);         // error: ) missing
    int s2 = area(7, 5);         // error: ; missing
    int s3 = area(7, 5);       // error: Int is not a type
    int s4 = area(7, 5);       // error: non-terminated character (' missing)
}

int area(int length, int width)
{
    int area = length*width;
    return area;
}