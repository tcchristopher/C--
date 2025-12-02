#ifndef ANXIETY_ITEM_H
#define ANXIETY_ITEM_H

#include <string>
#include <vector>
#include "action_step.h"
#include "category.h"

class AnxietyItem {
public:
    // Constructor
    AnxietyItem(std::string text, Category cat, int difficulty, int impact);

    // Getters
    std::string text() const;
    Category category() const;
    int difficulty() const;
    int impact() const;
    int priority() const;
    bool is_resolved() const;
    const std::vector<ActionStep>& steps() const;
    int completed_steps() const;
    int total_steps() const;
    double progress_percent() const;

    // Mutators - Actions
    void add_step(std::string step_text);
    void complete_step(int index);
    void resolve();

    // Mutators - Editing (for error correction)
    void set_text(const std::string& text);
    void set_category(Category cat);
    void set_difficulty(int diff);
    void set_impact(int imp);
    void remove_step(int index);
    void uncomplete_step(int index);

private:
    std::string m_text;
    Category m_category;
    int m_difficulty;
    int m_impact;
    bool m_resolved;
    std::vector<ActionStep> m_steps;
};

#endif