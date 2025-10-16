// A program that BLEEPS out bad words
#include <iostream>
#include <algorithm>

std::vector<std::string> disliked = {"fuck", "shit", "cunt", "bullshit", "fucker"};

int main()
{
    std::vector<std::string> words;
    for (std::string temp; std::cin >> temp; )
        words.push_back(temp);

    for (int i = 0; i < words.size(); ++i){
        if (std::find(disliked.begin(), disliked.end(), words[i]) != disliked.end()){
            std::cout << "BLEEP!" << '\n';
        }
        else {
            std::cout << words[i] << '\n';
        }
    }
}