// A prototype for a scorecard with entries logged in as dictionaries seperated into two vectors
#include <iostream>
#include <vector>
#include <string>

int lookup (std::vector<std::string> names, std::vector<int> scores);

int main()
{
    // Initialise variables for use
    std::vector<std::string> names;
    std::vector<int> scores;
    std::string buffer_name = " ";
    int buffer_score = 0;

    // Prompt user
    std::cout << "Please input the scores in the following format (Name #), keeping in mind the space between the name and the score.\n";
    std::cout << "Enter NoName 0 when done.\n";
    std::cout << "Begin: \n";

    // Get user input through an open While loop
    while (std::cin >> buffer_name >> buffer_score){
         // Close the input window with NoName 0
        if (buffer_name == "NoName" && buffer_score == 0){
            std::cout << "\nEntries closed.\n\n";
            break;
        }       
        // Else follow through on the vectorization of the data (push_back of buffer variables)
        else{
            // Search the names vector for the same name entered
            for (int i = 0; i < names.size(); ++i){
                // Error if name is found (output message and return 1)
                if (names[i] == buffer_name){
                    std::cout << "Repeated name found. Please check your data and try again with correct entries.\n";
                    return 1;
                }
            }          
            // Push_back into the vectors if the whole vector is traversed without an issue
            names.push_back(buffer_name);
            scores.push_back(buffer_score);
        }
    }

    // Check that names.size() == scores.size() or alternatively != and throw out Error message saying so and then return 1
    if (names.size() != scores.size()){
        std::cout << "Data entry corrupted - number of names entered does not match number of scores entered. Try again.\n";
        return 1;
    }

    // Output all Vector entries on seperate lines
    std::cout << "Scores:\n";
    for (int i = 0; i < names.size(); ++i){
        std::cout << names[i] << " " << scores[i] << '\n';
    }

    // TODO: Open up a new while loop window that asks the user for a choice to search the data list for
    while (true){
        lookup(names, scores);        
        break;
    }
}

// int lookup (std::vector<std::string> names, std::vector<int> scores)
// {
//     // TODO: Prompt user if they would like to search the lookup table. yes or no (if no, return at that point)
//     std::cout << "Would you like to search the list for entries? Type yes or no: ";
//     std::string answer = "";
//     std::cin >> answer;
//     if (answer == "no"){
//         return 1;
//         exit;
//     } 
//     else if (answer == "yes"){
//         // TODO: Create an if statement that asks the user if they would like to search for an name or a score
//         std::cout << "Please enter 'n' for name or 's' for score to search in the list: ";
//         char search = ' ';
//         std::cin >> search;
//         if (search == 'n'){
//             // TODO: Open up for user input for the names they would like to search the corresponding scores for
//             std::cout << "Please enter the name (mind your capitalization): ";
//             std::string search_name = "";
//             std::cin >> search_name;
//             for (int i = 0; i < names.size(); ++i){
//                 if (names[i] == search_name){
//                     std::cout << search_name << ": " << scores[i] << '\n';
//                 } 
//                 else {
//                     std::cout << "Name not found. Please try again.\n";
//                     std::exit(1);
//                 }
//             }
//         }
//         else if (search == 'y'){
//             // TODO: Open up for user input for the score they would like to match the corresponding names for
//             std::cout << "Please enter the score: ";
//             int search_score = 0;
//             std::cin >> search_score;
//             for (int i = 0; i < names.size(); ++i){
//                 if (scores[i] == search_score){
//                     std::cout << search_score << ": " << names[i] << '\n';
//                 } 
//                 else {
//                     std::cout << "Score not found. Please try again.";
//                     std::exit(1);
//                 }
//             }
//         }
//         else {
//             std::cout << "Wrong input chosen. Please try again with the correct input.";
//         }          
//     }
//     return 0;
// }
int lookup (std::vector<std::string> names, std::vector<int> scores)
{
    std::cout << "Would you like to search the list for entries? Type yes or no: ";
    std::string answer = "";
    std::cin >> answer;
    
    if (answer == "no"){
        return 1;
    } 
    else if (answer == "yes"){
        std::cout << "Please enter 'n' for name or 's' for score to search in the list: ";
        char search = ' ';
        std::cin >> search;
        
        if (search == 'n'){
            std::cout << "Please enter the name (mind your capitalization): ";
            std::string search_name = "";
            std::cin >> search_name;
            
            bool found = false;  // ← FLAG VARIABLE
            for (int i = 0; i < names.size(); ++i){
                if (names[i] == search_name){
                    std::cout << search_name << ": " << scores[i] << '\n';
                    found = true;
                    break;  // Found it, stop searching
                }
            }
            if (!found){
                std::cout << "Name not found.\n";
            }
        }
        else if (search == 's'){  // ← WAS 'y', SHOULD BE 's'!
            std::cout << "Please enter the score: ";
            int search_score = 0;
            std::cin >> search_score;
            
            bool found = false;
            for (int i = 0; i < scores.size(); ++i){
                if (scores[i] == search_score){
                    std::cout << names[i] << ": " << search_score << '\n';
                    found = true;  // Don't break - might be multiple people with same score
                }
            }
            if (!found){
                std::cout << "Score not found.\n";
            }
        }
        else {
            std::cout << "Wrong input chosen.\n";
        }          
    }
    return 0;
}