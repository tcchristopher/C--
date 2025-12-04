// AnxietyList Class implementation
// Implementation of the AnxietyList class.
// Handles the collection of anxieties including persistence.

#include "anxiety_list.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

// CONSTRUCTOR

AnxietyList::AnxietyList()
    : m_items() {}

// CORE OPERATIONS

// Adds a copy of the item to the end of the list
void AnxietyList::add(const AnxietyItem& item) {
    m_items.push_back(item);
}

// Removes item at index, shifting later items down.
// Uses bounds checking to prevent undefined behaviour.
void AnxietyList::remove(int index){
    if (index >= 0 && index <static_cast<int>(m_items.size())) {             // type safety for static_cast to prevent massive value errors in type conversion
        m_items.erase(m_items.begin() + index);
    }
}

// Returns modifiable reference for editing anxiety properties.
// Uses .at() which throws on invalid index.
AnxietyItem& AnxietyList::get(int index) {
    return m_items.at(index);
}

// Returns read-only reference for displaying anxiety properties.
// Uses .at() which throws on invalid index.
const AnxietyItem& AnxietyList::get(int index) const {
    return m_items.at(index);
}

// Returns total count of all anxieties (active + resolved).
int AnxietyList::size() const {
    return static_cast<int>(m_items.size());
}

// FILTERED ACCESS

// The next two items are pointers to the original data to allow for direct manipulation
// without having to jerryrig returning data from vectors etc.
std::vector<AnxietyItem*> AnxietyList::get_active() {
    std::vector<AnxietyItem*> result;
    for (auto& item : m_items) {
        if (!item.is_resolved()) {
            result.push_back(&item);
        }
    }
    return result;
}

// Returns pointers to resolved anxieties.
// Pointers allow caller to modify the original items.
std::vector<AnxietyItem*> AnxietyList::get_resolved() {
    std::vector<AnxietyItem*> result;
    for (auto& item : m_items) {
        if (item.is_resolved()) {
            result.push_back(&item);
        }
    }
    return result;
}

// SORTING

// Sorts anxieties for display.
// Sort order:
//   1. Unresolved items first
//   2. Within each group, higher priority first
void AnxietyList::sort_by_priority() {
    std::sort(m_items.begin(), m_items.end(), [](const AnxietyItem& a, const AnxietyItem& b) {
        // Sort by resolved status first (unresolved first)
        if (a.is_resolved() != b.is_resolved()) {
            return !a.is_resolved();
        }
        // Then by priority (higher first)
        return a.priority() > b.priority();
    });
}

// STATISTICS

// Counts anxieties that haven't been resolved yet.
int AnxietyList::active_count() const {
    int count = 0;
    for (const auto& item : m_items) {
        if (!item.is_resolved()) count++;
    }
    return count;
}

// Counts anxieties that have been resolved.
int AnxietyList::resolved_count() const{
    int count = 0;
    for (const auto& item : m_items) {
        if (item.is_resolved()) count++;
    }
    return count;
}

// Sums completed steps across all anxieties.
int AnxietyList::total_steps_completed() const {
    int count = 0;
    for (const auto& item : m_items) {
        count += item.completed_steps();
    }
    return count;
}

// FILE PERSISTENCE - (Critical for repeat usage - will update to more sophisticated solution post CS50x)

// Saves all data to a pipe-delimited text file.
// Format:
//   ANXIETY|category|difficulty|impact|resolved|text
//   STEP|anxiety_index|complete|text
//
// Returns false if file couldn't be opened.
bool AnxietyList::save(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) return false;

    // Header comment
    file << "# Anxiety Clarity Data File v1\n";

    for (int i = 0; i < static_cast<int>(m_items.size()); i++) {
        const auto& item = m_items[i];

        // Write anxiety line
        file    << "ANXIETY|"
                << category_to_string(item.category()) << "|"
                << item.difficulty() << "|"
                << item.impact() << "|"
                << (item.is_resolved() ? "true" : "false") << "|"
                << item.text() << "\n";

        // Write steps for this anxiety
        for (const auto& step : item.steps()) {
            file    << "STEP|"
                    << i << "|"
                    << (step.is_complete() ? "true" : "false") << "|"
                    << step.text() << "\n"; 
        }
    }
    return true;
}

// Loads data from a pipe-delimited text file.
// Clears existing data before loading.
// Tolerates corrupted lines - skips them and continues.
// Returns false if file couldn't be opened.
bool AnxietyList::load(const std::string& filename) {
    std::ifstream file(filename);
    if(!file) return false;

    m_items.clear();                    // Starts fresh
    std::string line;
    int line_number = 0;

    while (std::getline(file, line)) {
        line_number++;

        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') continue;

        try {
            std::stringstream ss(line);
            std::string type;
            std::getline(ss, type, '|');

            if (type == "ANXIETY") {
                // category|difficulty|impact|resolved|text
                std::string cat_str, diff_str, imp_str, res_str, text;
                std::getline(ss, cat_str, '|');
                std::getline(ss, diff_str, '|');
                std::getline(ss, imp_str, '|');
                std::getline(ss, res_str, '|');
                std::getline(ss, text);             // rest of line is text

                Category cat = string_to_category(cat_str);
                int diff = std::stoi(diff_str);
                int imp = std::stoi(imp_str);
                bool resolved = (res_str == "true");

                AnxietyItem item(text, cat, diff, imp);
                if (resolved) item.resolve();
                m_items.push_back(item);
            }
            else if (type == "STEP") {
                // anxiety_index|complete|text
                std::string idx_str, comp_str, text;
                std::getline(ss, idx_str, '|');
                std::getline(ss, comp_str, '|');
                std::getline(ss, text);

                int idx = std::stoi(idx_str);
                bool complete = (comp_str == "true");

                // Add step to the appropriate anxiety
                if (idx >= 0 && idx < static_cast<int>(m_items.size())) {
                    m_items[idx].add_step(text);
                    if (complete) {
                        int step_idx = m_items[idx].total_steps() - 1;
                        m_items[idx].complete_step(step_idx);
                    }
                }
            }
        } catch (const std::exception& e) {
            // Skip corrupted lines but continue loading
            std::cerr << "Warning: Could not parse line " << line_number << '\n';
        }
    }
    return true;
}