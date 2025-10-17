// A program to find the min, max and mode of a series of strings
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string input;
    std::vector<std::string> tester = {"mary", "had", "a", "a", "little", "little", "little", "lamb", "lamb"};
   // std::cout << "Please enter a series of strings for testing and enter * to close: \n";

    // while (input != "*"){
    //     std::cin >> input;
    //     tester.push_back(input);
    // }

    // Sort vector ascending order
    std::sort(tester.begin(), tester.end());

    // Print out min and max
    std::cout << "The minimum is: " << tester[0] << ". And the maximum is: " << tester[tester.size()-1] << ".\n";

    // Calculate the mode
    std::string mode = tester[0];
    int max_count = 1;
    int current_count = 1;

    for (int i = 1; i < tester.size(); ++i){
        if (tester[i] == tester[i-1])
            ++current_count;                    // Same string, increment count
        else{
            // Group of recurring strings ended - check if it's the biggest thus far
            if (current_count > max_count){
                max_count = current_count;
                mode = tester[i-1];             // The string we just finished counting
            }
            current_count = 1;                  // Reset counter for the new group
        }
    }

    //  Check the last group (being the recurring strings)
    if (current_count > max_count){
        max_count = current_count;
        mode = tester[tester.size()-1];         // Accesses the last vector item
    }

    //  Print out the mode
    std::cout << "The mode is: " << mode << " (appears " << max_count << " times)\n";
}