// A simple program to detect adjacent repeated words
#include <iostream>

int main()
{
    std::string previous = " ";     // previous word; initialized to "not a word"
    std::string current;            // current word
    while (std::cin >> current){
        if (previous == current)    // check if the word is the same as last
            std::cout << "Repeated word: " << current << '\n';
        previous = current;
    }
    return 0;
}