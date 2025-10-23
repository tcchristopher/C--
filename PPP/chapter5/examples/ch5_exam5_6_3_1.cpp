// Exception error handling for out_of_range and runtime_error
#include <iostream>
#include "std_lib_facilities.h"

int main()
try{
    // our program
    return 0;           // 0 indicates success
}
catch (exception& e){
    std::cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;           // 1 indicates failure
}
catch (...){
    std::cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;           // 2 indicates failure
}

void error (string s1, string s2)
{
    throw std::runtime_error(s1+s2);
}