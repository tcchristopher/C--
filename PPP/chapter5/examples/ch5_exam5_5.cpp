// Program with run-time errors
#include <iostream>

int area(int length, int width);
int framed_area(int x, int y);

int main()
{
    int x = -1;
    int y = 2;
    int z = 4;
    // ...
    int area1 = area(x,y);                  // will result in -2
    int area2 = framed_area(1, z);          // will result in -2
    int area3 = framed_area(y, z);          // will result in 0
    double ratio = double (area1)/area3;    // will result in -2/0 = undefined/infinity

    std::cout << area1 << '\n';
    std::cout << area2 << '\n';
    std::cout << area3 << '\n';
    std::cout << ratio << '\n';
    
    return 0;
}

int area(int length, int width)             // calculate area of a rectangle
{
    return length*width;
}

int framed_area(int x, int y)              // calculate area within a frame
{
    return area(x-2, y-2);
}