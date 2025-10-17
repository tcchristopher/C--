// A literal rice grain counter for the chessboard problem (it's a power series question)
#include <iostream>

int main()
{
    double current_rice = 1;
    double sum_of_rice = 0;

    for (int i = 1; i <= 64; ++i){
        sum_of_rice += current_rice;
        std::cout << "The rice on the current (" << i << ") square is: " << current_rice << " and the total rice is " << sum_of_rice << ".\n";
        current_rice *= 2;
    }
}