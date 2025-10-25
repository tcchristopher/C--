// Bulls and Cows
#include <iostream>
#include <vector>
#include <string>

int main()
{
    // Initialise variables and a storage vector for the number to be guessed (TODO: random numbers)
    std::vector<int>gen_num = {3,4,6,9};
    std::vector<int>guess;
    int temp = 0;

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

        // Check to see if the right number of integers were entered:
        if (guess.size() != 4){
            std::cerr << "You have not input the correct number of integers. Try again.\n";
            return 1;
        }

        // // Check that the numbers are in the same and in the same position
        // for (int i = 0; i < gen_num.size(); ++i){
        //     // flag that the cow has been seen before
        //     bool cow_flag = false;
        //     // check the vectors
        //     if (guess[i] == gen_num[i]){
        //         ++bulls;
        //     } else {
        //         if ((std::count(gen_num.begin(), gen_num.end(), guess[i])>0) && !cow_flag){
        //             ++cows;
        //             cow_flag = true;
        //         }
        //     }
        // }

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

}