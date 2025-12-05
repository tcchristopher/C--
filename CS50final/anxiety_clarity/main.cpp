// Entry point for Anxiety Clarity, a project manager of sorts to help the user declutter their mind
// of endless anxieties and worries through creating a self-direction action plan list for each anxiety
// Handles the main menu loop and program lifecycle.
// main.cpp
// Entry point for Anxiety Clarity.
// Handles the main menu loop and program lifecycle.

#include <iostream>
#include "anxiety_list.h"
#include "ui.h"

// Data file for persistence
const std::string DATA_FILE = "anxieties.txt";

int main() {
    AnxietyList list;

    // Load existing data (silently succeeds if file doesn't exist)
    list.load(DATA_FILE);

    // Main program loop
    while (true) {
        display_main_menu(list);

        int choice = get_int_input("Choice: ", 1, 4);

        switch (choice) {
            case 1:
                work_on_anxiety(list);
                break;

            case 2:
                add_new_anxiety(list);
                break;

            case 3:
                display_victories(list);
                break;

            case 4:
                // Save and exit
                if (list.save(DATA_FILE)) {
                    clear_screen();
                    std::cout << "╔══════════════════════════════════════╗\n";
                    std::cout << "║                                      ║\n";
                    std::cout << "║        ✓ Progress saved.             ║\n";
                    std::cout << "║                                      ║\n";
                    std::cout << "║   You've done great work!            ║\n";
                    std::cout << "║   Return when you're ready.          ║\n";
                    std::cout << "║                                      ║\n";
                    std::cout << "╚══════════════════════════════════════╝\n\n";
                } else {
                    std::cout << "\n⚠ WARNING: Could not save data!\n";
                    std::cout << "Check file permissions.\n\n";

                    if (confirm_yes_no("Try again?")) {
                        continue;  // Loop back to try saving again
                    }
                }
                return 0;  // Exit program
        }
    }

    return 0;
}