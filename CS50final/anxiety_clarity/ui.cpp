#include "ui.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <cctype>

void clear_screen() {
    std::cout << "\033[2J\033[1;1H";
}

void wait_for_enter() {
    std::cout << "\n[Press Enter to continue]";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int get_int_input(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;

        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (value >= min && value <= max) {
                return value;
            } else {
                std::cout   << "\nPlease enter a number between "
                            << min << " and " << max << ".\n\n";
            }
        } else{
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nThat's not a valid number. Please try again.\n\n";
        }
    }
}

std::string get_string_input(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline (std::cin, input);
    return input;
}

std::string get_required_string(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        // Cut whitespace
        size_t start = input.find_first_not_of(" \t\n\r");
        size_t end = input.find_last_not_of(" \t\n\r");

        if (start == std::string::npos) {
            std::cout << "\nThis field can't be empty. Please enter something.\n\n";
        } else {
            return input.substr(start, end - start + 1);
        }
    }
}

