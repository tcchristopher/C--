// A program to play a numbers guessing game
#include <iostream>

int guesser(char guess_answer, int& upper_range, int& lower_range);

int main()
{
    // Initialise the boundary checkers
    int upper_range = 100;
    int lower_range = 0;

    // Initialise a counter to keep track of the number of guesses
    int counter = 0; 

    // Start off the initial guess
    std::cout << "You're thinking of a number between 1 and 100.";
    char guess_answer = ' ';
    char final_answer = ' ';
    
    // Do the iterations
    while (upper_range - lower_range > 2){
        std::cout << "Is the number less than " << (upper_range+lower_range)/2 << "? Type y for yes, n for no\n";
        std::cin >> guess_answer;
        guesser(guess_answer, upper_range, lower_range);
        ++counter;
    }
    std::cout << "Is your number " << (upper_range+lower_range)/2 << "? Type y for yes, n for no.\n";
    std::cin >> final_answer;
    ++counter;
    if (final_answer == 'y'){
        std::cout << "Perfect! Thank you. That took " << counter << " tries.\n";
    } 
    else if (final_answer == 'n'){
        std::cout << "Ah, then your number is " << lower_range << ". That took " << counter << " tries.\n";
    }
}

int guesser(char guess_answer, int& upper_range, int& lower_range)
//                                    ↑                 ↑
//                            These & make them references
{
    if (guess_answer == 'y'){
        upper_range = (upper_range+lower_range)/2;
        return upper_range;
    }
    else if (guess_answer =='n'){
        lower_range = (upper_range+lower_range)/2;
        return lower_range;
    }
    else{
        std::cout << "Please enter the correct answer.";
        std::cin >> guess_answer;
        return guesser(guess_answer, upper_range, lower_range);
    }
}