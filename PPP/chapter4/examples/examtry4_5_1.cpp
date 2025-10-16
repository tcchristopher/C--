// Create a square calculator without any multiplication
#include <iostream>

int square(int x);              // Declaration of the square

int main(){
    std::cout << "Please enter a number to be squared: \n";
    int num = 0;
    std::cin >> num;
    std::cout << "The square of " << num << " is " << square(num) << ".\n";
}



// Squaring funcion
int square(int x)
{
    int sum = 0;
    for(int i = 0; i < x; ++i){
        sum += x;
    }
    return sum;
}