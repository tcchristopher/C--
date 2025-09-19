#include <iostream>

int main()
{
    int a = 42;
    int b = 10;
    std::cout << a << " " << b << std::endl;
    std::cout << a + b << std::endl;

    int age = 39;
    std::string first = "Thabiso";
    std::string last = "Christopher";
    std::string name = first + " " + last;

    std::cout << name << " " << age << std::endl;

    return 0;
}