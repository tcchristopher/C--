#include "action_step.h"

ActionStep::ActionStep(std::string text)
    : m_text(text), m_complete(false)
{
    // Body empty - initialization list does the work
}

std::string ActionStep::text() const {
    return m_text;
}

bool ActionStep::is_complete() const {
    return m_complete;
}

void ActionStep::complete(){
    m_complete = true;
}