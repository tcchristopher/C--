// Name-value pairs functions from Chapter 4 Exercise 19 reworked for classes
#include <iostream>
#include <vector>
#include <string>
// #include "std_lib_facilities.h"

// Declare classes
class name_value {
public:
    // Constructor
    name_value(std::string n, int s) 
        : name(n), score(s) { }
    
    // Accessors (getters)
    std::string get_name() const { return name; }
    int get_score() const { return score; }
    
private:
    std::string name;
    int score;
};

int lookup(std::vector<name_value> entries);

int main()
{
    std::vector<name_value> entries;
    std::string buffer_name = " ";
    int buffer_score = 0;

    std::cout << "Please input the scores in the following format (Name #).\n";
    std::cout << "Enter NoName 0 when done.\n";
    std::cout << "Begin: \n";

    while (std::cin >> buffer_name >> buffer_score) {
        if (buffer_name == "NoName" && buffer_score == 0) {
            std::cout << "\nEntries closed.\n\n";
            break;
        }       
        
        // Check for duplicate names
        bool duplicate = false;
        for (const auto& entry : entries) {
            if (entry.get_name() == buffer_name) {
                std::cout << "Repeated name found. Please check your data.\n";
                return 1;
            }
        }
        
        // Single operation to add the pair!
        entries.push_back(name_value{buffer_name, buffer_score});
    }

    // No size check needed - impossible for sizes to differ!
    
    std::cout << "Scores:\n";
    for (const auto& entry : entries) {
        std::cout << entry.get_name() << " " << entry.get_score() << '\n';
    }

    lookup(entries);
}

int lookup(std::vector<name_value> entries)
{
    std::cout << "Would you like to search the list? (yes/no): ";
    std::string answer;
    std::cin >> answer;
    
    if (answer == "no") return 1;
    
    if (answer == "yes") {
        std::cout << "Search by 'n' (name) or 's' (score): ";
        char search;
        std::cin >> search;
        
        if (search == 'n') {
            std::cout << "Enter name: ";
            std::string search_name;
            std::cin >> search_name;
            
            bool found = false;
            for (const auto& entry : entries) {
                if (entry.get_name() == search_name) {
                    std::cout << entry.get_name() << ": " 
                             << entry.get_score() << '\n';
                    found = true;
                    break;
                }
            }
            if (!found) std::cout << "Name not found.\n";
        }
        else if (search == 's') {
            std::cout << "Enter score: ";
            int search_score;
            std::cin >> search_score;
            
            bool found = false;
            for (const auto& entry : entries) {
                if (entry.get_score() == search_score) {
                    std::cout << entry.get_name() << ": " 
                             << entry.get_score() << '\n';
                    found = true;
                }
            }
            if (!found) std::cout << "Score not found.\n";
        }
    }
    return 0;
}