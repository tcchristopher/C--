#include <iostream>

int main()
{
    int n1, n2 = 0;
    std::cout << "Please enter two numbers:" << std::endl;
    std::cin >> n1 >> n2;
    int count = std::min(n1, n2);   // Set the counter to the lowest of the two values entered

    while (count <= std::max(n1, n2))   // Condtional based on the counter reaching the maximum number inclusive
    {
        std::cout << count << std::endl;
        count++;
    }
    return 0;
}