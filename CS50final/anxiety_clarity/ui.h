#ifndef UI_H
#define UI_H

#include <string>
#include "anxiety_list.h"

// Screen Utilities
void clear_screen();
void wait_for_enter();

// Input Utilities (with validation)
int get_int_input(const std::string& prompt, int min, int max);
std::string get_string_input(const std::string& prompt);
std::string get_required_string(const std::string& prompt);
char get_char_input(const std::string& prompt);
bool confirm_yes_no(const std::string& prompt);
bool confirm_destructive(const std::string& prompt, const std::string& confirm_word);

// Display Functions
void display_main_menu(const AnxietyList& list);
void display_all_anxieties(AnxietyList& list);
void display_anxiety_detail(AnxietyItem& item, int index);
void display_victories(const AnxietyList& list);

// Action Functions
void add_new_anxiety(AnxietyList& list);
void work_on_anxiety(AnxietyList& list);

// Edit/Delete Functions
void edit_anxiety(AnxietyItem& item);
void delete_anxiety(AnxietyList& list, int index);
void edit_step(AnxietyItem& item);
void delete_step(AnxietyItem& item);

// Celebration Functions
void celebrate_step_complete(const std::string& step_text, double progress);
void celebrate_anxiety_resolved(const std::string& anxiety_text, int total_victories);

// Helper Functions
std::string progress_bar(double percent, int width);

#endif