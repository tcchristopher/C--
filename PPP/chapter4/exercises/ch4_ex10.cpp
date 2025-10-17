// Rock-Paper-Scissors
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>


int main()
{
    srand(time(0));
    std::vector<std::string>game = {"rock", "paper", "scissors"};
    char player_choice = 'a';
    std::cout << "Play your choice: 'r' for rock, 'p' for paper, 's' for scissors.\n";
    while (std::cin >> player_choice){
        int computer_choice = rand() % 3;

        switch(player_choice){
        case 'r':
            if (game[computer_choice] == "rock")
                std::cout << "Your choice was rock. The computer choose " << game[computer_choice] << ". Draw.\n";
            else if (game[computer_choice] == "paper")
                std::cout << "Your choice was rock. The computer choose " << game[computer_choice] << ". You lose.\n";
            else if (game[computer_choice] == "scissors")
                std::cout << "Your choice was rock. The computer choose " << game[computer_choice] << ". You win.\n";
            else
                std::cout << "No choice is the wrong choice, sucka! YOU LOSE!\n";
            break;
        
        case 'p':
            if (game[computer_choice] == "rock")
                std::cout << "Your choice was paper. The computer choose " << game[computer_choice] << ". You win.\n";
            else if (game[computer_choice] == "paper")
                std::cout << "Your choice was paper. The computer choose " << game[computer_choice] << ". Draw.\n";
            else if (game[computer_choice] == "scissors")
                std::cout << "Your choice was paper. The computer choose " << game[computer_choice] << ". You lose.\n";
            else
                std::cout << "No choice is the wrong choice, sucka! YOU LOSE!\n";
            break;

        case 's':
            if (game[computer_choice] == "rock")
                std::cout << "Your choice was scissors. The computer choose " << game[computer_choice] << ". You lose.\n";
            else if (game[computer_choice] == "paper")
                std::cout << "Your choice was scissors. The computer choose " << game[computer_choice] << ". You win.\n";
            else if (game[computer_choice] == "scissors")
                std::cout << "Your choice was scissors. The computer choose " << game[computer_choice] << ". Draw.\n";
            break;

        default:
            std::cout << "No choice is the wrong choice, sucka! YOU LOSE!\n";
            break;
        }
    }
    return 0;
}