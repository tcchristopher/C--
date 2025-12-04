// Implementation of the ActionStep class

#include "action_step.h"

// CONSTRUCTOR

// Creates a new incomplete action step with the given description
ActionStep::ActionStep(std::string text)
    : m_text(text), m_complete(false)
{
    // Body is empty - initialization list does the work
}

// GETTERS

// Returns the step's text description
std::string ActionStep::text() const {
    return m_text;
}

// Returns whether the step is complete or not
bool ActionStep::is_complete() const {
    return m_complete;
}

// MUTATORS

// Marks the step as done
void ActionStep::complete(){
    m_complete = true;
}

// Reverts the step to incomplete state.
// Useful for correcting mistakes.
void ActionStep::uncomplete(){
    m_complete = false;
}