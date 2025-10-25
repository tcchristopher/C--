// Bulls and Cows, with play again and randomiser for the numbers
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

int main()
{
    // Randomise time
    srand(time(0));

    // Play again?
    bool play_again = true;
    while (play_again){

        // Initialise variables and a storage vector for the number to be guessed
        std::vector<int>guess;
        int temp = 0;

        // Generate 4 random numbers (0-9)
        std::vector<int>gen_num;
        while (gen_num.size() < 4){
            int digit = rand() % 10;        // random number between 0 and 9

            // Check if this number is already in gen_num (no duplicates)
            bool already_exists = false;
            for (int i=0; i < gen_num.size(); ++i){
                if (gen_num[i] == digit){
                    already_exists = true;
                    break;
                }
            }

            if (!already_exists){
                gen_num.push_back(digit);
            }
        }

        // Create counts for bulls and cows
        int bulls = 0;
        int cows = 0;

        // Track which positions are already matched
        std::vector<bool> gen_used(4, false);
        std::vector<bool> guess_used(4, false);

        // Create a while loop for bulls < 4, looping the entire interaction until satisfied.
        while(bulls < 4){
            
            // Clear the vectors, bulls and cows
            guess.clear();
            bulls = 0;
            cows = 0;
            gen_used = {false, false, false, false};
            guess_used = {false, false, false, false};

            // Load in the user's guess
            std::cout << "Please enter your guess as seperate integer numbers between 0 and 9:\n";
            while (guess.size() < 4)
            {
                std::cin >> temp;
                if (temp < 0 || temp >9){
                    std::cerr << temp << " is not a valid number in the range of 0 and 9.\n";
                    std::cerr << "Please enter a valid number:\n";
                } else{
                    guess.push_back(temp);
                }
            }

            // Check for duplicates in the guess
            for (int i=0; i < guess.size(); ++i){
                for (int j = i + 1; j < guess.size(); ++j){
                    if (guess[i] == guess[j]){
                        std::cerr << "You entered duplicate digits. Please enter 4 unique digits.\n";
                        guess.clear();
                        break;
                    }
                }
                if (guess.empty()) break;       // Duplicates found
            }
            if (guess.size() != 4) continue;

            // Check to see if the right number of integers were entered:
            if (guess.size() != 4){
                std::cerr << "You have not input the correct number of integers. Try again.\n";
                return 1;
            }

            // First pass: count bulls and mark positions as used
            for (int i = 0; i < 4; ++i){
                if ((guess[i] == gen_num[i]) && !gen_used[i]){
                    ++bulls;
                    gen_used[i] = true;
                    guess_used[i] = true;
                }
            }

            // Second pass: count cows (only for unmatched positions in bulls)
            for (int i = 0; i < 4; ++i){
                if (!guess_used[i]){ // Not a bull
                    for(int j=0; j < 4; ++j){
                        if (!gen_used[j] && guess[i] == gen_num[j]){
                            ++cows;
                            gen_used[j] = true; // lock it off
                            break;              // Match found so stop searching for this digit
                        }
                    }
                }
            }


            // Output the number of bulls and cows
            // Naming
            std::string bull_text = "bulls";
            std::string cow_text = "cows";
            if (bulls == 1)
                bull_text = "bull";
            if (cows == 1)
                cow_text = "cow";

            std::cout << bulls << " " << bull_text << " and " << cows << " " << cow_text << '\n';
        }

        std::cout << "Hey man, nice shot! Play again? (y/n): ";
        char response;
        std::cin >> response;
        if (response != 'y' && response != 'Y')
            play_again = false;
    }
    
    return 0;
}