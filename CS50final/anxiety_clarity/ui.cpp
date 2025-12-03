// UI function implementations

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

char get_char_input(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input.empty() ? '\0' : input[0];
}

bool confirm_yes_no(const std::string& prompt) {
    while (true) {
        std::cout << prompt << " [Y/N]: ";
        std::string input;
        std:getline(std::cin, input);

        if (input.empty()) continue;

        char c = std::toupper(input[0]);
        if (c == 'Y') return true;
        if (c == 'N') return false;

        std::cout << "\nPlease enter Y or N.\n\n";
    }
}

bool confirm_destructive(const std::string& prompt, const std::string& confirm_word) {
    std::cout << prompt << '\n';
    std::cout << "Type " << confirm_word << " to confirm, or anything else to cancel: ";

    std::string input;
    std::getline(std::cin, input);

    return input == confirm_word;
}

std::string progress_bar (double percent, int width) {
    int filled = static_cast<int>((percent/100.0) * width);
    std::string bar = "";
    for (int i = 0; i < width; i++) {
        if (i < filled) bar += "█";
        else bar += "░";
    }
    return bar;
}

void display_main_menu(const AnxietyList& list){
    clear_screen();
    std::cout   << "╔══════════════════════════════════════╗\n";
    std::cout   << "║         ANXIETY CLARITY              ║\n";
    std::cout   << "║   Project Management for Your Mind   ║\n";
    std::cout   << "╠══════════════════════════════════════╣\n";
    std::cout   << "║                                      ║\n";
    std::cout   << "║  Active anxieties: " << std::left << std::setw(17) 
                << list.active_count() << "║\n";
    std::cout   << "║  Resolved (victories): " << std::left << std::setw(13) 
                << list.resolved_count() << "║\n";
    std::cout   << "║                                      ║\n";
    std::cout   << "║  [1] View All Anxieties              ║\n";
    std::cout   << "║  [2] Add New Anxiety                 ║\n";
    std::cout   << "║  [3] Work on an Anxiety              ║\n";
    std::cout   << "║  [4] View Victories                  ║\n";
    std::cout   << "║  [5] Save & Exit                     ║\n";
    std::cout   << "║                                      ║\n";
    std::cout   << "╚══════════════════════════════════════╝\n";
    std::cout   << '\n';
}

void display_all_anxieties(AnxietyList& list) {
    clear_screen();
    list.sort_by_priority();

    std::cout << "YOUR ANXIETIES (sorted by priority - highest first)\n";
    std::cout << "═══════════════════════════════════════════════════════════════\n\n";

    if (list.size() == 0) {
        std::cout << "No anxieties yet. That's either great news or\n";
        std::cout << "you haven't add any yet, which is also okay.\n";
        std::cout << "Let's work through them together.\n";
    } else {
        std::cout << "#  │ PRI │ CATEGORY │ ANXIETY                         │ PROGRESS\n";
        std::cout << "───┼─────┼──────────┼─────────────────────────────────┼──────────\n";

        for (int i = 0; i < list.size(); i++) {
            const auto& item = list.get(i);

            std::string text = item.text();
            if (text.length() > 30) {
                text = text.substr(0, 27) + "...";
            }

            std::string progress;
            if (item.is_resolved()) {
                progress = "done";
            } else if (item.total_steps() == 0) {
                progress = "no steps";
            } else {
                progress =  std::to_string(item.completed_steps()) + "/" +
                            std::to_string(item.total_steps());
            }

            std::cout   << std::left << std::setw(3) << (i + 1)
                        << "| " << std::setw(4) << item.priority()
                        << "| " << std::setw(9) << category_to_string(item.category())
                        << "| " << std::setw(32) << text
                        << "| " << progress;

            if (item.is_resolved()) std::cout << " ★";
            std::cout << '\n';
        }
    }
    std::cout   << "\n═══════════════════════════════════════════════════════════════\n";
    std::cout   << "Active: " << list.active_count()
                << "  │  Resolved: " << list.resolved_count()
                << "  │  Steps completed: " << list.total_steps_completed() << '\n';
    std::cout   << "\n[Enter #] to work on it    [B] Back to menu\n";
}