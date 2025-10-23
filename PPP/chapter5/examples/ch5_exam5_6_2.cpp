// Range errors example
#include <iostream>
#include "std_lib_facilities.h"

int main()
try {
    vector<int> v;                      // a vector of ints
    for (int x; std::cin >> x; )
        v.push_back(x);                 // set values
    for (int i =0; i <= v.size(); ++i)  // print values
        std::cout << "v[" << i << "] ==" << v[i] << '\n';
} catch (out_of_range){
    std::cerr << "Oops! Range error\n";
    return 1;
} catch(...){                           // catch all other exceptions
    std::cerr << "Exception: something went wrong\n";
    return 2;
}
