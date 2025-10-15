// A program for counting which words (by number location) repeat
#include <iostream>

int main()
{
    int number_of_words = 0;
    std::string previous = " ";     // not a word
    std::string current;
    while (std::cin >> current){
        ++number_of_words;          // increase word count at the very beginning
        if (previous == current)
            std::cout << "Word number " << number_of_words
            << " repeated: " << current << '\n';
        previous = current;
    }
    return 0;   
}