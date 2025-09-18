#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item book;
    if (std::cin >> book)
    {
        Sales_item sum(book);           //  Initialise sum with first book's value to correctly format it
        std::cout << "The total thus far is: " << sum << std::endl;  //  Output the first book's value.
        while (std::cin >> book)
        {
            sum += book;
            std::cout << "The total thus far is: " << sum << std::endl;
        }
    }
    return 0;
}