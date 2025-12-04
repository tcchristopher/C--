// ActionStep class headers
// Defines the ActionStep class - represents a single actionable task 
// that can be completed to make progress on an anxiety item.

#ifndef ACTION_STEP_H
#define ACTION_STEP_H

#include <string>

class ActionStep {
public:    
    // CONSTRUCTOR

    // Creates a new action step with the given text desciption.
    // The step starts in an incomplete state
    ActionStep(std::string text);

    // GETTERS

    // Returns the text description of the step
    std::string text() const;

    // Returns true if this step has been marked complete
    bool is_complete() const;

    // MUTATORS
    
    // Marks the step as complete 
    void complete();

    // Marks the step as incomplete (undo a completion)
    // Used when a user accidentally marks the wrong step as complete
    void uncomplete();

private:
    std::string m_text;                     // Description of the action to take
    bool m_complete;                        // Completion status
};

#endif