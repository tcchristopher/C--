//  This program outputs the message "Hello, World!" to the monitor
//  Curiously, Stroustrup doesn't using std::endl here.
//  Interesting - Stroustrup actually recommends not using it as it flushes the stream, perhaps prematurely and expensively
//  Nor iostream
//  Okay so Stroustrup had a full custom library for standard includes, being "std_lib_facilities.h"

#include <iostream>

int main()
{
    std::cout << "Hello, World!\n";
    return 0;
}