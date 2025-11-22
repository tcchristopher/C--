#include <iostream>

void swap_v(int a, int b);
void swap_r(int& a, int& b);
void swap_cr(const int& a, const int& b);


int main()
{
    // variables
    int x = 7;
    int y = 9;
    std::cout << "before x is " << x << ", before y is " << y << '\n';
    swap_v(x,y);
    std::cout << "swap_v x is " << x << ", swap_v y is " << y << '\n';
    swap_r(x,y);
    std::cout << "swap_r x is " << x << ", swap_r y is " << y << '\n';
    swap_cr(x,y);
    std::cout << "swap_cr x is " << x << ", swap_cr y is " << y << '\n';

   
    // variables
    const int cx = 7;
    const int cy = 9;
    std::cout << "before cx is " << cx << ", before cy is " << cy << '\n';
    swap_v(cx,cy);
    std::cout << "swap_v cx is " << cx << ", swap_v cy is " << cy << '\n';
//    swap_r(cx,cy);
//    std::cout << "swap_r cx is " << cx << ", swap_r cy is " << cy << '\n';
    swap_cr(cx,cy);
    std::cout << "swap_cr cx is " << cx << ", swap_cr cy is " << cy << '\n';


    // variables 
    double dx = 7.7;
    double dy = 9.9;
    std::cout << "before dx is " << dx << ", before dy is " << dy << '\n';
    swap_v(dx,dy);
    std::cout << "swap_v dx is " << dx << ", swap_v dy is " << dy << '\n';
//    swap_r(dx,dy);
//    std::cout << "swap_r dx is " << dx << ", swap_r dy is " << dy << '\n';
    swap_cr(dx,dy);
    std::cout << "swap_cr dx is " << dx << ", swap_cr dy is " << dy << '\n';
}

void swap_v(int a, int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swap_r(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swap_cr(const int& a, const int& b)
{
    int temp;
    temp = a;
//    a = b;
//    b = temp;
}