#include "anxiety_item.h"

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

int AnxietyItem::priority() const {
    return m_difficulty * m_impact;
}

int AnxietyItem::total_steps() const {
    return static_cast<int>(m_steps.size());
}

int AnxietyItem::completed_steps() const {
    int count = 0;
    for (const auto& step : m_steps) {
        if (step.is_complete()) {
            count++;
        }
    }
    return count;
}

double AnxietyItem::progress_percent() const {
    if (m_steps.empty()) {
        return m_resolved ? 100.0 : 0.0;
    }
    return (static_cast<double>(completed_steps()) / total_steps()) * 100.0;
}

void AnxietyItem::add_step(std::string step_text) {
    m_steps.push_back(ActionStep(step_text));
}

void AnxietyItem::complete_step(int index) {
    if (index >= 0 && index < static_cast<int>(m_steps.size())) {
        m_steps[index].complete();
    }
}

void AnxietyItem::resolve() {
    m_resolved = true;
}

void AnxietyItem::set_text(const std::string& text) {
    m_text = text;
}

void AnxietyItem::set_category(Category cat) {
    m_category = cat;
}

void AnxietyItem::set_difficulty(int diff) {
    if (diff < 1) diff =1;
    if (diff > 10) diff = 10;
    m_difficulty = diff;
}

void AnxietyItem::set_impact(int imp) {
    if (imp < 1) imp = 1;
    if (imp > 10) imp = 10;
    m_impact = imp;
}

void AnxietyItem::remove_step(int index) {
    if (index >= 0 && index < static_cast<int>(m_steps.size())) {
        m_steps.erase(m_steps.begin() + index);
    }
}

void AnxietyItem::uncomplete_step(int index) {
    if (index >= 0 && index < static_cast<int>(m_steps.size())) {
        m_steps[index].uncomplete();
    }
}