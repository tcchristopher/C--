// A simple dictionary of vectors
#include <iostream>

int main()
{
    std::vector<std::string> words;
    for (std::string temp; std::cin >> temp; )
        words.push_back(temp);
    std::cout << "Number of words: " << words.size() << '\n';

    std::sort(words.begin(), words.end());

    for (int i = 0; i < words.size(); ++i)
        if (i==0 || words[i-1] != words[i])         // first it starts things off if we have no word, then it continues to ask if this is a new word
            std::cout << words[i] << "\n";          // as a result, it will output every new word in the dictionary
}