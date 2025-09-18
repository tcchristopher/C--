#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item book1, book2;
    std::cin >> book1 >> book2;
    //  first check if the ISBN's are the same
    if (book1.isbn() == book2.isbn())
    {
        std::cout << book1 + book2 << std::endl;
        return 0;   // indicate success
    }
    else{
        std::cout << "Data input must refer to the same ISBN" << std::endl;
        return -1;  // indicate failure
    }
}