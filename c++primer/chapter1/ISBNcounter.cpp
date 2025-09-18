#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item book, bookTotal;      // bookTotal is the total sum of transactions for any book set; read new books into book
    if (std::cin >> bookTotal){      // read the first book data to have data to process
        int count = 1;              // store the number of books of the same ISBN
        while (std::cin >> book){   // read the new book data into book
            if(book.isbn() == bookTotal.isbn())
            {
                bookTotal += book; //
                ++count;
            }
            else{
                std::cout << bookTotal << " was sold over " << count << " transactions." << std::endl;
                bookTotal = book;
                count = 1;
            }
        }
        std::cout << bookTotal << " was sold over " << count << " transactions." << std::endl;
    }
    return 0;
}