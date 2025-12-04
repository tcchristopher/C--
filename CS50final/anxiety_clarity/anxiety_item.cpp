// Implementation of the AnxietyItem class

#include "anxiety_item.h"

// CONSTRUCTOR

// Creates a new anxiety with validated difficulty and impact ratings.
// Values outside 1-10 are limited/clamped to the valid range.
AnxietyItem::AnxietyItem(std::string text, Category cat, int difficulty, int impact)
    : m_text(text)
    , m_category(cat)
    , m_difficulty(difficulty)
    , m_impact(impact)
    , m_resolved(false)
    , m_steps()
{
    // Limit difficulty and impact to 1-10 range
    if (m_difficulty < 1) m_difficulty = 1;
    if (m_difficulty > 10) m_difficulty = 10;
    if (m_impact < 1) m_impact = 1;
    if (m_impact > 10) m_impact = 10;
}

// GETTERS

std::string AnxietyItem::text() const {
    return m_text;
}

Category AnxietyItem::category() const {
    return m_category;
}

int AnxietyItem::difficulty() const {
    return m_difficulty;
}

int AnxietyItem::impact() const {
    return m_impact;
}

bool AnxietyItem::is_resolved() const {
    return m_resolved;
}

const std::vector<ActionStep>& AnxietyItem::steps() const {
    return m_steps;
}

// PROPERTIES, calculated during runtime

// Priority determines sort order. Higher priority = more urgent.
// Formula: difficulty × impact gives range 1-100.
int AnxietyItem::priority() const {
    return m_difficulty * m_impact;
}

// Returns the total number of action steps.
int AnxietyItem::total_steps() const {
    return static_cast<int>(m_steps.size());           // type safety for static_cast to prevent massive value errors in type conversion
}

// Counts how many steps have been marked complete.
int AnxietyItem::completed_steps() const {
    int count = 0;
    for (const auto& step : m_steps) {
        if (step.is_complete()) {
            count++;
        }
    }
    return count;
}

// Calculates percentage of steps completed.
// Edge cases:
//   - No steps + resolved = 100%
//   - No steps + not resolved = 0%
double AnxietyItem::progress_percent() const {
    if (m_steps.empty()) {
        return m_resolved ? 100.0 : 0.0;
    }
    return (static_cast<double>(completed_steps()) / total_steps()) * 100.0;
}

// MUTATORS (actions)

// Adds a new incomplete step to the end of the steps list.
void AnxietyItem::add_step(std::string step_text) {
    m_steps.push_back(ActionStep(step_text));
}

// Marks the step at index as complete.
// Bounds-checked to prevent crashes.
void AnxietyItem::complete_step(int index) {
    if (index >= 0 && index < static_cast<int>(m_steps.size())) {
        m_steps[index].complete();
    }
}

// Marks this anxiety as resolved
void AnxietyItem::resolve() {
    m_resolved = true;
}

// MUTATORS (edits)

void AnxietyItem::set_text(const std::string& text) {
    m_text = text;
}

void AnxietyItem::set_category(Category cat) {
    m_category = cat;
}

// Updates difficulty with range validation.
void AnxietyItem::set_difficulty(int diff) {
    if (diff < 1) diff =1;
    if (diff > 10) diff = 10;
    m_difficulty = diff;
}

// Updates impact with range validation.
void AnxietyItem::set_impact(int imp) {
    if (imp < 1) imp = 1;
    if (imp > 10) imp = 10;
    m_impact = imp;
}

// Removes step at index.
// Bounds-checked to prevent crashes.
void AnxietyItem::remove_step(int index) {
    if (index >= 0 && index < static_cast<int>(m_steps.size())) {
        m_steps.erase(m_steps.begin() + index);
    }
}

// Reverts a step to incomplete state.
// Bounds-checked to prevent crashes.
void AnxietyItem::uncomplete_step(int index) {
    if (index >= 0 && index < static_cast<int>(m_steps.size())) {
        m_steps[index].uncomplete();
    }
}