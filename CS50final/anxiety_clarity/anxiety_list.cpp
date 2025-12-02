#include "anxiety_list.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

AnxietyList::AnxietyList()
    : m_items() {}

void AnxietyList::add(const AnxietyItem& item) {
    m_items.push_back(item);
}

void AnxietyList::remove(int index){
    if (index >= 0 && index <static_cast<int>(m_items.size())) {             // type safety for static_cast to prevent massive value errors in type conversion
        m_items.erase(m_items.begin() + index);
    }
}

// For modifying list items
AnxietyItem& AnxietyList::get(int index) {
    return m_items.at(index);
}

// For just reading only
const AnxietyItem& AnxietyList::get(int index) const {
    return m_items.at(index);
}

int AnxietyList::size() const {
    return static_cast<int>(m_items.size());
}

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

std::vector<AnxietyItem*> AnxietyList::get_resolved() {
    std::vector<AnxietyItem*> result;
    for (auto& item : m_items) {
        if (item.is_resolved()) {
            result.push_back(&item);
        }
    }
    return result;
}

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

int AnxietyList::active_count() const {
    int count = 0;
    for (const auto& item : m_items) {
        if (!item.is_resolved()) count++;
    }
    return count;
}

int AnxietyList::resolved_count() const{
    int count = 0;
    for (const auto& item : m_items) {
        if (item.is_resolved()) count++;
    }
    return count;
}

int AnxietyList::total_steps_completed() const {
    int count = 0;
    for (const auto& item : m_items) {
        count += item.completed_steps();
    }
    return count;
}

bool AnxietyList::save(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) return false;

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

bool AnxietyList::load(const std::string& filename) {
    std::ifstream file(filename);
    if(!file) return false;

    m_items.clear();
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
                std::string cat_str, diff_str, imp_str, res_str, text;
                std::getline(ss, cat_str, '|');
                std::getline(ss, diff_str, '|');
                std::getline(ss, imp_str, '|');
                std::getline(ss, res_str, '|');
                std::getline(ss, text);

                Category cat = string_to_category(cat_str);
                int diff = std::stoi(diff_str);
                int imp = std::stoi(imp_str);
                bool resolved = (res_str == "true");

                AnxietyItem item(text, cat, diff, imp);
                if (resolved) item.resolve();
                m_items.push_back(item);
            }
            else if (type == "STEP") {
                std::string idx_str, comp_str, text;
                std::getline(ss, idx_str, '|');
                std::getline(ss, comp_str, '|');
                std::getline(ss, text);

                int idx = std::stoi(idx_str);
                bool complete = (comp_str == "true");

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