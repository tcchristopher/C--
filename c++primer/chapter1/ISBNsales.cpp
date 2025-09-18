#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item book1, book2;
    std::cin >> book1 >> book2;
    if (book1.isbn() == book2.isbn())
    {
        std::cout << "The total for the books is: " << book1 + book2 << std::endl;
    }
    else{
        std::cout << "The books entered do not have the same ISBN" << std::endl;
    }
    return 0;
}