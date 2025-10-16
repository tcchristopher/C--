// A simple program that output the squares of every number up to 100
#include <iostream>
#include "std_lib_facilities.h"

int main()
{
    int i = 0;          // start from 0
    while(i<100){
        std::cout << i << '\t' << i*i << '\n';
        ++i;
    }
    return 0;
}