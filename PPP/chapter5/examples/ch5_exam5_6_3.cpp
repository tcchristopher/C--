// Bad input examples
#include <iostream>
#include <vector>
#include "std_lib_facilities.h"

int main()
try {
    // ... our program ...
    return 0;                   // 0 indicates success
}
catch (std::runtime_error& e){
    std::cerr << "runtime error: " << e.what() << '\n';
    keep_window_open();
    return 1;                   // 1 indicates failure
}