#ifndef ACTION_STEP_H
#define ACTION_STEP_H

#include <string>

class ActionStep {
public:    
    // Constructor
    ActionStep(std::string text);

    // Getters
    std::string text() const;
    bool is_complete() const;

    // Mutators
    void complete();

private:
    std::string m_text;
    bool m_complete;
};

#endif