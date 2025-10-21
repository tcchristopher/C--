// Program with run-time errors
// With all of the fixes in the caller area, it's hella ugly. It's better to deal with this in callee area (function space)
#include <iostream>
#include "std_lib_facilities.h"

int area(int length, int width);
int framed_area(int x, int y);

constexpr int frame_width = 2;

int main()
{
    int x = -1;
    int y = 2;
    int z = 4;
    // ...
    if (x <= 0) error("non-positive x");
    if (y <= 0) error("non-positive y");
    int area1 = area(x,y);                  // will result in -2
    if (z <= 2)
        error("non-positive 2nd area() argument called by framed_area()");
    if (1-frame_width<=0 || z-frame_width<=0)
        error("non-positive argument for area() called by framed_area()");
    int area2 = framed_area(1, z);          // will result in -2
    if (y <= 2 || z <= 2)
        error("non-positive area() argument called by framed_area()");
    if (y-frame_width <=0 || z-frame_width<=0)
        error("non-positive argument for area() called by framed_area()");
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
    return area(x-frame_width, y-frame_width);
}