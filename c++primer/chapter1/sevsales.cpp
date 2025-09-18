#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item book;
    if (std::cin >> book)
    {
        Sales_item sum(book);
        while (std::cin >> book)
        {
            if (book.isbn() == sum.isbn())
            {
                sum += book;
            }
            else{
                std::cout << "The book entered does not match the ISBN needed: " << sum.isbn() << std::endl;
                break;
            }
        }
        std::cout << "The total is: " << sum << std::endl;
    }
    return 0;
}