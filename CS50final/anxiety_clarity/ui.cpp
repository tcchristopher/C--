// Implementation of all user interface functions.
// Handles display, input validation, and user interactions.

#include "ui.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <cctype>


// SCREEN UTILITIES

// Clears terminal using ANSI escape sequences.
// \033[2J = clear screen, \033[1;1H = move cursor to top-left
void clear_screen() {
    std::cout << "\033[2J\033[1;1H";
}

// Displays prompt and waits for Enter key.
// Uses ignore() to consume any characters in the buffer.
void wait_for_enter() {
    std::cout << "\n[Press Enter to continue]";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// INPUT UTILITIES
// Robustly gets an integer within a specified range.
// Handles non-numeric input and out-of-range values.
// Loops until valid input is received.

int get_int_input(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;

        if (std::cin >> value) {
            // Clear remaining characters (e.g., newline)            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (value >= min && value <= max) {
                return value;                               // valid input
            } else {
                std::cout   << "\nPlease enter a number between "
                            << min << " and " << max << ".\n\n";
            }
        } else{
            // Input wasn't a number - clear error and discard bad input
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nThat's not a valid number. Please try again.\n\n";
        }
    }
}

// Gets a string that can be empty (for optional fields).
std::string get_string_input(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline (std::cin, input);
    return input;
}

// Gets a non-empty string (for required fields).
// Trims whitespace and loops until content is provided.
std::string get_required_string(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);

        // Cut whitespace
        size_t start = input.find_first_not_of(" \t\n\r");
        size_t end = input.find_last_not_of(" \t\n\r");

        if (start == std::string::npos) {
            // String is empty or is all whitespace
            std::cout << "\nThis field can't be empty. Please enter something.\n\n";
        } else {
            // Return trimmed string
            return input.substr(start, end - start + 1);
        }
    }
}

// Gets a single character (first character of input).
// Returns null character if user just presses Enter.
char get_char_input(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input.empty() ? '\0' : input[0];
}

// Prompts for Y/N response, case-insensitive.
// Loops until valid response is given.
bool confirm_yes_no(const std::string& prompt) {
    while (true) {
        std::cout << prompt << " [Y/N]: ";
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) continue;

        char c = std::toupper(input[0]);
        if (c == 'Y') return true;
        if (c == 'N') return false;

        std::cout << "\nPlease enter Y or N.\n\n";
    }
}

// Requires exact word match for dangerous operations.
// Prevents accidental deletion.
bool confirm_destructive(const std::string& prompt, const std::string& confirm_word) {
    std::cout << prompt << '\n';
    std::cout << "Type " << confirm_word << " to confirm, or anything else to cancel: ";

    std::string input;
    std::getline(std::cin, input);

    return input == confirm_word;               // Exact match required
}

// HELPER FUNCTION

// Creates a text-based progress bar.
// Uses filled (█) and empty (░) block characters.
std::string progress_bar (double percent, int width) {
    int filled = static_cast<int>((percent/100.0) * width);
    std::string bar = "";
    for (int i = 0; i < width; i++) {
        if (i < filled) bar += "█";
        else bar += "░";
    }
    return bar;
}

// DISPLAY FUNCTION

// Shows the main menu inside a decorative box.
// Displays current active and resolved counts.
void display_main_menu(const AnxietyList& list){
    clear_screen();
    std::cout   << "╔══════════════════════════════════════╗\n";
    std::cout   << "║         ANXIETY CLARITY              ║\n";
    std::cout   << "║   Project Management for Your Mind   ║\n";
    std::cout   << "╠══════════════════════════════════════╣\n";
    std::cout   << "║                                      ║\n";
    std::cout   << "║  Active anxieties: " << std::left << std::setw(17) 
                << list.active_count() << " ║\n";
    std::cout   << "║  Resolved (victories): " << std::left << std::setw(13) 
                << list.resolved_count() << " ║\n";
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

// Displays all anxieties in a formatted table.
// Sorts by priority before display.
// Shows progress and marks resolved items with a star.
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
        // Table header
        std::cout << "#  │ PRI │ CATEGORY │ ANXIETY                         │ PROGRESS\n";
        std::cout << "───┼─────┼──────────┼─────────────────────────────────┼──────────\n";

        for (int i = 0; i < list.size(); i++) {
            const auto& item = list.get(i);

            // Truncate long text with ellipsis
            std::string text = item.text();
            if (text.length() > 30) {
                text = text.substr(0, 27) + "...";
            }

            // Format progress column
            std::string progress;
            if (item.is_resolved()) {
                progress = "done";
            } else if (item.total_steps() == 0) {
                progress = "no steps";
            } else {
                progress =  std::to_string(item.completed_steps()) + "/" +
                            std::to_string(item.total_steps());
            }

            // Print row
            std::cout   << std::left << std::setw(3) << (i + 1)
                        << "| " << std::setw(4) << item.priority()
                        << "| " << std::setw(9) << category_to_string(item.category())
                        << "| " << std::setw(32) << text
                        << "| " << progress;

            if (item.is_resolved()) std::cout << " ★";
            std::cout << '\n';
        }
    }

    // Footer with summary stats
    std::cout   << "\n═══════════════════════════════════════════════════════════════\n";
    std::cout   << "Active: " << list.active_count()
                << "  │  Resolved: " << list.resolved_count()
                << "  │  Steps completed: " << list.total_steps_completed() << '\n';
    std::cout   << "\n[Enter #] to work on it    [B] Back to menu\n";
}

// Shows detailed view of a single anxiety.
// Includes all properties, steps with completion status, and action menu.
void display_anxiety_detail(AnxietyItem& item, int index) {
    clear_screen();
    std::cout << "ANXIETY #" << (index + 1) << ": " << item.text() << '\n';
    std::cout << "═══════════════════════════════════════════════════════════════\n\n";

    // Display properties with visual progress bars
    std::cout   << "Category:    " << category_to_string(item.category()) << '\n';
    std::cout   << "Difficulty:  " << progress_bar(item.difficulty() * 10, 10)
                << " (" << item.difficulty() << "/10)\n";
    std::cout   << "Impact:      " << progress_bar(item.impact() * 10, 10)
                << " (" << item.impact() << "/10)\n";
    std::cout   << "Priority:    " << item.priority();
    if (item.priority() >= 70) std::cout << " (CRITICAL)";
    else if (item.priority() >= 40) std::cout << " (HIGH)";
    std::cout << '\n';

    // Display action steps with checkboxes
    std::cout << "\nYOUR ACTION STEPS:\n";
    if (item.total_steps() == 0) {
        std::cout << " (No steps yet - add some to break this down)\n";
    } else {
        const auto& steps = item.steps();
        for (int i = 0; i < static_cast<int>(steps.size()); i++) {
            std::cout   << "  [" << (steps[i].is_complete() ? "✓" : " ") << "] "
                        << (i + 1) << ". " << steps[i].text() << '\n';
        }
    }
    // Overall progress
    std::cout   << "\nProgress: " << progress_bar(item.progress_percent(), 16)
                << " " << static_cast<int>(item.progress_percent()) << "%\n";
    
    // Action menu
    std::cout << "\n───────────────────────────────────────────────────────────────\n";
    std::cout << "[A] Add new step       [C] Complete a step\n";
    std::cout << "[E] Edit anxiety       [D] Delete anxiety\n";
    std::cout << "[R] Resolve (done!)    [B] Back\n";
}

// Shows all resolved anxieties as a victory list.
void display_victories(const AnxietyList& list) {
    clear_screen();
    std::cout << "YOUR VICTORIES\n";
    std::cout << "═══════════════════════════════════════════════════════════════\n\n";
    
    std::cout << "These anxieties no longer have power over you:\n\n";
    
    int victory_count = 0;
    for (int i = 0; i < list.size(); i++) {
        const auto& item = list.get(i);
        if (item.is_resolved()) {
            victory_count++;
            std::cout << victory_count << ". ★ " << item.text() 
                    << " (" << category_to_string(item.category()) << ")\n";
            std::cout << "   Resolved with " << item.completed_steps() 
                    << " step(s) completed\n\n";
        }
    }
    
    if (victory_count == 0) {
        std::cout << "(No victories yet. Keep working - they'll come.)\n\n";
    }
    
    std::cout << "═══════════════════════════════════════════════════════════════\n";
    std::cout << "Total victories: " << victory_count << "\n";
    std::cout << "Total steps conquered: " << list.total_steps_completed() << "\n";
    
    if (victory_count > 0) {
        std::cout << "\nYou have proof that you can handle your life.\n";
    }
    
    std::cout << "\n[B] Back to menu\n";
    get_char_input("");
}


// ACTION FUNCTIONS

// Guides user through creating a new anxiety with optional steps.
// Shows preview and asks for confirmation before saving.
void add_new_anxiety(AnxietyList& list) {
    clear_screen();
    std::cout << "ADD NEW ANXIETY\n";
    std::cout << "═══════════════════════════════════════\n\n";

    // Get description
    std::cout << "What's got you worried?\n";
    std::cout << "(Put it in your own words)\n\n";
    std::string text = get_required_string("> ");

    // Get category from menu
    std::cout << "\nCategory:\n";
    std::cout << "  [1] INCOME      [5] WORK\n";
    std::cout << "  [2] BILLS       [6] HOUSING\n";
    std::cout << "  [3] FAMILY      [7] RELATIONSHIPS\n";
    std::cout << "  [4] HEALTH      [8] OTHER\n\n";
    int cat_choice = get_int_input("Select category: ", 1, 8);

    Category cat;
    switch (cat_choice) {
        case 1: cat = Category::INCOME; break;
        case 2: cat = Category::BILLS; break;
        case 3: cat = Category::FAMILY; break;
        case 4: cat = Category::HEALTH; break;
        case 5: cat = Category::WORK; break;
        case 6: cat = Category::HOUSING; break;
        case 7: cat = Category::RELATIONSHIPS; break;
        default: cat = Category::OTHER; break;
    }

    // Get difficulty rating
    std::cout << "\nHow DIFFICULT does this feel? On a scale of (1-10)\n";
    std::cout << "(1 = easy to handle, 10 = overwhelming)\n";
    int difficulty = get_int_input("> ", 1, 10);

    // Get impact rating
    std::cout << "\nHow much IMPACT does this have on your life? On a scale of (1-10)\n";
    std::cout << "(1 = minor, 10 = affects everything)\n";
    int impact = get_int_input("> ", 1, 10);

    // Create an anxiety item for the list
    AnxietyItem item(text, cat, difficulty, impact);

    // Prompt for steps
    std::cout << "\nLet's break it down. What's ONE step you could take to addressing it?\n";
    std::cout << "(Press Enter to skip for now, or type a step)\n";

    while (true) {
        std::string step = get_string_input("\n> ");
        if (step.empty()) break;

        item.add_step(step);
        std::cout << "Step added! Let's try add one more step? (or press Enter to finish)";
    }

    // Show summary for confirmation
    std::cout   << "\n───────────────────────────────────────\n";
    std::cout   << "REVIEW YOUR ENTRY\n\n";
    std::cout   << "\"" << text << "\"\n";
    std::cout   << "Category:   " << category_to_string(cat) << '\n';
    std::cout   << "Difficulty: " << progress_bar(difficulty * 10, 10)
                << " (" << difficulty << "/10)\n";
    std::cout   << "Impact:     " << progress_bar(impact * 10, 10)
                << " (" << impact << "/10)\n";
    std::cout   << "Priority:   " << (difficulty * impact);
    
    if (difficulty * impact >= 70) std::cout << " (CRITICAL)";
    else if (difficulty * impact >= 40) std::cout << " (HIGH)";
    std::cout << '\n';

    if (item.total_steps() > 0) {
        std::cout << "\nSteps:\n";
        for (int i = 0; i < item.total_steps(); i++) {
            std::cout << "  " << (i + 1) << ". " << item.steps()[i].text() << '\n';
        }
    }

    std::cout << "\n───────────────────────────────────────\n";

    // Confirm before saving
    while (true) {
        char confirm = get_char_input("Save this anxiety? [Y]es / [N]o / [E]dit: ");
        confirm = std::toupper(confirm);

        if (confirm == 'Y') {
            list.add(item);
            std::cout << "\nAnxiety saved.\n";
            if (item.total_steps() > 0) {
                std::cout   << "You've gotten to work at it in just " << item.total_steps()
                            << " step(s). That's the journey!\n";
            } else {
                std::cout << "You've started this journey!\n";
            }
            break;
        } else if (confirm == 'N') {
            std::cout << "\nDiscarded. Nothing saved.\n";
            break;
        } else if (confirm == 'E') {
            std::cout << "\nLet's start over.\n";
            wait_for_enter();
            add_new_anxiety(list);
            return;
        } else {
            std::cout << "\nPlease enter Y, N, or E.\n";
        }
    }
    wait_for_enter();
}

// Main interaction loop for working on existing anxieties.
// Allows selecting an anxiety and performing actions on it.
void work_on_anxiety(AnxietyList& list) {
    while (true) {
        display_all_anxieties(list);

        std::string input = get_string_input("\nChoice: ");

        if (input.empty()) continue;
        if (input[0] == 'B' || input[0] == 'b') return;

        // Try to parse as a number
        int choice;
        try {
            choice = std::stoi(input);
        } catch (...) {
            continue;       // Not a number, loop again
        }

        // Validate range
        if (choice < 1 || choice > list.size()) {
            std::cout << "\nPlease enter a number between 1 and " << list.size() << ".\n";
            wait_for_enter();
            continue;
        }

        int index = choice - 1;
        AnxietyItem& item = list.get(index);

        // Inner loop for working on selected anxiety
        while(true) {
            display_anxiety_detail(item, index);

            char action = get_char_input("\nChoice: ");
            action = std::toupper(action);
            
            if (action == 'B') break;               // back to list

            if (action == 'A') {
                // Add new step
                std::string step_text = get_string_input("New step: ");
                if (!step_text.empty()) {
                    item.add_step(step_text);
                    std::cout << "Step added!\n";
                    wait_for_enter();
                }
            }
            else if (action == 'C') {
                // Complete a step
                if (item.total_steps() == 0) {
                    std::cout << "\nNo steps to complete. Add some first.\n";
                    wait_for_enter(); 
                } else {
                    int step_num = get_int_input("Which step? ", 1, item.total_steps());
                    int step_idx = step_num - 1;

                    if (item.steps()[step_idx].is_complete()) {
                        std::cout << "\nThat step is already complete.\n";
                        wait_for_enter();
                    } else {
                        std::cout << "\nMark as complete: \"" << item.steps()[step_idx].text() << "\"\n";
                        if (confirm_yes_no("Are you sure?")) {
                            item.complete_step(step_idx);
                            celebrate_step_complete(
                                item.steps()[step_idx].text(),
                                item.progress_percent()
                            );
                        } else {
                            std::cout << "Cancelled.\n";
                            wait_for_enter();
                        }
                    }
                }
            }
            else if (action == 'E') {
                edit_anxiety(item);
            }
            else if (action == 'D') {
                delete_anxiety(list, index);
                break;          // Return to list after deletion
            }
            else if (action == 'R') {
                // Resolve the anxiety
                std::cout << "\n═══════════════════════════════════════\n";
                std::cout << "        RESOLVE THIS ANXIETY?\n\n";
                std::cout << "\"" << item.text() << "\"\n\n";
                std::cout << "This will move it to your Victories list.\n";

                if (confirm_yes_no("Are you sure?")) {
                    item.resolve();
                    celebrate_anxiety_resolved(item.text(), list.resolved_count());
                    break;  // Return to list after resolving
                } else {
                    std::cout << "Cancelled.\n";
                    wait_for_enter();
                }
            }
        }
    }
}

// CELEBRATION FUNCTIONS

// Shows a celebratory screen when a step is completed.
// Displays progress towards resolving the anxiety.
void celebrate_step_complete(const std::string& step_text, double progress) {
    clear_screen();
    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║                                      ║\n";
    std::cout << "║            ✓ STEP COMPLETE           ║\n";
    std::cout << "║                                      ║\n";
    
    // Truncate long text
    std::string display_text = step_text;
    if (display_text.length() > 34) {
        display_text = display_text.substr(0, 31) + "...";
    }
    std::cout << "║   \"" << std::left << std::setw(33) << display_text << "\"║\n";
    
    std::cout << "║                                      ║\n";
    std::cout << "║   ─────────────────────────────────  ║\n";
    std::cout << "║                                      ║\n";
    std::cout << "║   Progress: " << std::setw(3) << static_cast<int>(progress) << "%"
            << "                     ║\n";
    std::cout << "║   " << std::left << std::setw(24) << progress_bar(progress, 20) << "      ║\n";
    std::cout << "║                                      ║\n";
    std::cout << "║                                      ║\n";
    std::cout << "╚══════════════════════════════════════╝\n";
    
    wait_for_enter();
  }

// Shows a victory celebration when an anxiety is resolved.
// Displays motivational message and victory count.
void celebrate_anxiety_resolved(const std::string& anxiety_text, int total_victories) {
    clear_screen();
    std::cout << "╔══════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                                                              ║\n";
    std::cout << "║                      ★ VICTORY ★                             ║\n";
    std::cout << "║                                                              ║\n";
    
    std::string text = anxiety_text;
    if (text.length() > 55) {
        text = text.substr(0, 52) + "...";
    }
    std::cout << "║   \"" << std::left << std::setw(57) << text << "\"║\n";
    
    std::cout << "║                                                              ║\n";
    std::cout << "║              IS NO LONGER EATING YOU UP                      ║\n";
    std::cout << "║                                                              ║\n";
    std::cout << "║   ════════════════════════════════════════════════════════   ║\n";
    std::cout << "║                                                              ║\n";
    std::cout << "║   You faced it.                                              ║\n";
    std::cout << "║   You worked through it.                                     ║\n";
    std::cout << "║   You OVERCAME it!                                           ║\n";
    std::cout << "║                                                              ║\n";
    std::cout << "║   ────────────────────────────────────────────────────────   ║\n";
    std::cout << "║                                                              ║\n";
    std::cout << "║   Total victories: " << std::left << std::setw(41) << total_victories << " ║\n";
    std::cout << "║   You can overcome anything!                                 ║\n";
    std::cout << "║                                                              ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════════╝\n";
    
    wait_for_enter();
}

// EDIT/DELETE FUNCTIONS

// Menu-driven interface for editing anxiety properties and steps.
void edit_anxiety(AnxietyItem& item) {
    while (true) {
        clear_screen();
        std::cout << "EDIT ANXIETY\n";
        std::cout << "═══════════════════════════════════════\n\n";
        
        // Show current values as menu options
        std::cout << "[1] Text: \"" << item.text() << "\"\n";
        std::cout << "[2] Category: " << category_to_string(item.category()) << "\n";
        std::cout << "[3] Difficulty: " << item.difficulty() << "/10\n";
        std::cout << "[4] Impact: " << item.impact() << "/10\n";
        std::cout << "[5] Edit a step\n";
        std::cout << "[6] Delete a step\n";
        std::cout << "[7] Undo a completed step\n";
        std::cout << "[B] Back (keep changes)\n";
        
        char choice = get_char_input("\nChoice: ");
        choice = std::toupper(choice);
        
        if (choice == 'B') return;
        
        switch (choice) {
            case '1': {
                // Edit text
                std::cout << "\nCurrent: \"" << item.text() << "\"\n";
                std::cout << "New text (Enter to keep current): ";
                std::string new_text;
                std::getline(std::cin, new_text);
                if (!new_text.empty()) {
                    item.set_text(new_text);
                    std::cout << "Updated.\n";
                }
                wait_for_enter();
                break;
            }
            case '2': {
                // Edit category
                std::cout << "\nCategory:\n";
                std::cout << "  [1] INCOME      [5] WORK\n";
                std::cout << "  [2] BILLS       [6] HOUSING\n";
                std::cout << "  [3] FAMILY      [7] RELATIONSHIPS\n";
                std::cout << "  [4] HEALTH      [8] OTHER\n\n";
                int cat = get_int_input("Select category: ", 1, 8);
                Category new_cat;
                switch (cat) {
                    case 1: new_cat = Category::INCOME; break;
                    case 2: new_cat = Category::BILLS; break;
                    case 3: new_cat = Category::FAMILY; break;
                    case 4: new_cat = Category::HEALTH; break;
                    case 5: new_cat = Category::WORK; break;
                    case 6: new_cat = Category::HOUSING; break;
                    case 7: new_cat = Category::RELATIONSHIPS; break;
                    default: new_cat = Category::OTHER; break;
                }
                item.set_category(new_cat);
                std::cout << "Updated.\n";
                wait_for_enter();
                break;
            }
            case '3': {
                // Edit difficulty
                std::cout << "\nCurrent difficulty: " << item.difficulty() << "/10\n";
                int new_diff = get_int_input("New difficulty (1-10): ", 1, 10);
                item.set_difficulty(new_diff);
                std::cout << "Updated. New priority: " << item.priority() << '\n';
                wait_for_enter();
                break;
            }
            case '4': {
                // Edit impact
                std::cout << "\nCurrent impact: " << item.impact() << "/10\n";
                int new_imp = get_int_input("New impact (1-10): ", 1, 10);
                item.set_impact(new_imp);
                std::cout << "Updated. New priority: " << item.priority() << '\n';
                wait_for_enter();
                break;
            }
            case '5':
                edit_step(item);
                break;
            case '6':
                delete_step(item);
                break;
            case '7': {
                // Undo a completed step
                const auto& steps = item.steps();
                std::cout << "\nCompleted steps:\n";
                bool found = false;
                for (int i = 0; i < static_cast<int>(steps.size()); i++) {
                    if (steps[i].is_complete()) {
                        std::cout << "  [" << (i+1) << "] " << steps[i].text() << '\n';
                        found = true;
                    }
                }
                if (!found) {
                    std::cout << "  (No completed steps to undo)\n";
                    wait_for_enter();
                } else {
                    int step_num = get_int_input("Which step to uncomplete (0 to cancel): ", 0, item.total_steps());
                    if (step_num > 0) {
                        item.uncomplete_step(step_num - 1);
                        std::cout << "Step marked as incomplete.\n";
                    }
                    wait_for_enter();
                }
                break;
            }
        }
    }
}

// Allows editing the text of an existing step.
// Preserves completion status after edit.
void edit_step(AnxietyItem& item) {
    if (item.total_steps() == 0) {
        std::cout << "\nNo steps to edit.\n";
        wait_for_enter();
        return;
    }
    
    // Show all steps
    std::cout << "\nWhich step to edit?\n";
    const auto& steps = item.steps();
    for (int i = 0; i < static_cast<int>(steps.size()); i++) {
        std::cout << "  [" << (i+1) << "] " << steps[i].text() << '\n';
    }
    
    int step_num = get_int_input("\nStep number (0 to cancel): ", 0, item.total_steps());
    if (step_num == 0) return;
    
    std::cout << "\nCurrent: \"" << steps[step_num-1].text() << "\"\n";
    std::string new_text = get_string_input("New text (Enter to keep): ");
    
    if (!new_text.empty()) {
        // Preserve completion status during edit
        bool was_complete = steps[step_num-1].is_complete();
        item.remove_step(step_num - 1);
        item.add_step(new_text);
        if (was_complete) {
            item.complete_step(item.total_steps() - 1);
        }
        std::cout << "Step updated.\n";
    }
    wait_for_enter();
}

// Deletes a step after confirmation
void delete_step(AnxietyItem& item) {
    if (item.total_steps() == 0) {
        std::cout << "\nNo steps to delete.\n";
        wait_for_enter();
        return;
    }
    
    // Show all steps
    std::cout << "\nWhich step to delete?\n";
    const auto& steps = item.steps();
    for (int i = 0; i < static_cast<int>(steps.size()); i++) {
        std::cout << "  [" << (i+1) << "] " << steps[i].text() << '\n';
    }
    
    int step_num = get_int_input("\nStep number (0 to cancel): ", 0, item.total_steps());
    if (step_num == 0) return;
    
    std::cout << "\nDelete \"" << steps[step_num-1].text() << "\"?\n";
    if (confirm_yes_no("Are you sure?")) {
        item.remove_step(step_num - 1);
        std::cout << "Step deleted.\n";
    } else {
        std::cout << "Cancelled.\n";
    }
    wait_for_enter();
}

// Deletes an entire anxiety after requiring user to type DELETE.
// Extra confirmation prevents accidental data loss.
void delete_anxiety(AnxietyList& list, int index) {
    clear_screen();
    const auto& item = list.get(index);
    
    std::cout << "═══════════════════════════════════════\n";
    std::cout << "         DELETE THIS ANXIETY?\n\n";
    std::cout << "\"" << item.text() << "\"\n\n";
    std::cout << "  This will permanently delete this anxiety\n";
    std::cout << "  and all " << item.total_steps() << " step(s).\n";
    std::cout << "  This cannot be undone.\n\n";
    
    if (confirm_destructive("", "DELETE")) {
        list.remove(index);
        std::cout << "\nAnxiety deleted.\n";
    } else {
        std::cout << "\nCancelled. Nothing deleted.\n";
    }
    
    wait_for_enter();
}