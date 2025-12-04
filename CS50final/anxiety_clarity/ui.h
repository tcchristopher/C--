// UI function declarations
// Declares all user interface functions for the CLI.
// Handles display, input validation, and user interactions.

#ifndef UI_H
#define UI_H

#include <string>
#include "anxiety_list.h"


// SCREEN UTILITIES

// Clears the terminal screen using ANSI escape codes.
void clear_screen();

// Pauses execution until user presses Enter.
void wait_for_enter();


// INPUT UTILITIES (with validation)

// Prompts for an integer within [min, max] range.
// Loops until valid input is received.
int get_int_input(const std::string& prompt, int min, int max);

// Prompts for a string. Can be empty (optional input).
std::string get_string_input(const std::string& prompt);

// Prompts for a non-empty string. Loops until content provided.
// Trims leading/trailing whitespace.
std::string get_required_string(const std::string& prompt);

// Prompts for a single character.
// Returns '\0' if user just presses Enter.
char get_char_input(const std::string& prompt);

// Prompts for Y/N confirmation.
// Loops until valid response. Returns true for Y, false for N.
bool confirm_yes_no(const std::string& prompt);

// Prompts user to type a specific word to confirm destructive action.
// Returns true only if input exactly matches confirm_word.
bool confirm_destructive(const std::string& prompt, const std::string& confirm_word);


// DISPLAY FUNCTIONS

// Shows the main menu with active/resolved counts.
void display_main_menu(const AnxietyList& list);

// Shows all anxieties in a sorted table format.
void display_all_anxieties(AnxietyList& list);

// Shows detailed view of a single anxiety with its steps.
void display_anxiety_detail(AnxietyItem& item, int index);

// Shows the list of resolved anxieties (victories).
void display_victories(const AnxietyList& list);


// ACTION FUNCTIONS

// Guides user through adding a new anxiety with steps.
void add_new_anxiety(AnxietyList& list);

// Main interaction loop for working on anxieties.
void work_on_anxiety(AnxietyList& list);


// EDIT/DELETE FUNCTIONS

// Menu for editing anxiety properties and steps.
void edit_anxiety(AnxietyItem& item);

// Prompts for confirmation then deletes an anxiety.
void delete_anxiety(AnxietyList& list, int index);

// Allows editing the text of a step.
void edit_step(AnxietyItem& item);

// Prompts for confirmation then deletes a step.
void delete_step(AnxietyItem& item);


// CELEBRATION FUNCTIONS

// Displays congratulations when a step is completed.
void celebrate_step_complete(const std::string& step_text, double progress);

// Displays victory celebration when anxiety is resolved.
void celebrate_anxiety_resolved(const std::string& anxiety_text, int total_victories);


// HELPER FUNCTIONS

// Returns a progress bar string using block characters.
// percent: 0-100, width: number of characters
std::string progress_bar(double percent, int width);

#endif