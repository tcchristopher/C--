// A program that converts numbers to their spoken words and back again
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string>words = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::cout << "Please enter the number (int) or a word between 0 and 9: \n";
    std::string input;
    while(std::cin >> input){
        // Check if input is a word in the vector
        int i = 0;
        for (i = 0; i < words.size(); ++i){
            if(input == words[i]){
                std::cout << i << '\n';
                break;
            }
        }
        // if we didn't find it as a word
        if (i == words.size()){
            // check if it's a single digit
            if (input.length() == 1 && input[0] >= '0' && input[0] <= '9'){             // ASCII number logic here
                int number = input[0] - '0';
                std::cout << words[number] << '\n';
            } else{
                std::cout << "I don't know that number.\n";
            }
        }
    }
    return 0;
}