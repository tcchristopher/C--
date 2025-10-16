// A program that traverses a vector and outputs the values on screen
#include <iostream>

int main()
{
    std::vector<int> v = {5, 7, 9, 4, 6, 8};
    for(int i=0; i<v.size(); ++i)
        std::cout << v[i] << '\n';

    for(int x : v)                              // for each x in v (a range for loop)
        std::cout << x << '\n';                 // Like Python!
    
    return 0;
}