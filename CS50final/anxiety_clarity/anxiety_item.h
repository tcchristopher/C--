// AnxietyItem class headers
// Defines the AnxietyItem class - represents a single anxiety with
// its category, ratings, action steps, and resolution status.

#ifndef ANXIETY_ITEM_H
#define ANXIETY_ITEM_H

#include <string>
#include <vector>
#include "action_step.h"
#include "category.h"

class AnxietyItem {
public:
    // CONSTRUCTOR

    // Creates a new anxiety item with the given properties.
    // Difficulty and impact are clamped to 1-10 range.
    // The item starts unresolved with no action steps.
    AnxietyItem(std::string text, Category cat, int difficulty, int impact);

    // GETTERS

    // Returns the text description of this anxiety.
    std::string text() const;
    
    // Returns the category this anxiety belongs to.
    Category category() const;
    
    // Returns difficulty rating (1-10). Higher = harder to handle.
    int difficulty() const;
    
    // Returns impact rating (1-10). Higher = affects life more.
    int impact() const;
    
    // Returns priority score (difficulty × impact).
    // Range: 1-100. Used for sorting anxieties.
    int priority() const;
    
    // Returns true if this anxiety has been resolved.
    bool is_resolved() const;
    
    // Returns read-only access to the list of action steps.
    const std::vector<ActionStep>& steps() const;
    
    // Returns the number of steps marked complete.
    int completed_steps() const;
    
    // Returns the total number of action steps.
    int total_steps() const;
    
    // Returns completion percentage (0-100).
    // Returns 0 if no steps, 100 if resolved with no steps.
    double progress_percent() const;

    // MUTATORS

    // Adds a new action step to this anxiety.
    void add_step(std::string step_text);
    
    // Marks the step at the given index as complete.
    // Does nothing if index is out of range.
    void complete_step(int index);
    
    // Marks this anxiety as resolved (victory!).
    void resolve();
    
    // === Edit Mutators ===
    // These allow users to correct mistakes.
    
    // Updates the anxiety description text.
    void set_text(const std::string& text);
    
    // Changes the category.
    void set_category(Category cat);
    
    // Updates difficulty rating (limited to 1-10).
    void set_difficulty(int diff);
    
    // Updates impact rating (limited to 1-10).
    void set_impact(int imp);
    
    // Removes the step at the given index.
    // Does nothing if index is out of range.
    void remove_step(int index);
    
    // Marks a completed step as incomplete (undo).
    // Does nothing if index is out of range.
    void uncomplete_step(int index);

private:
    std::string m_text;              // Description of the anxiety
    Category m_category;             // Classification
    int m_difficulty;                // How hard it feels (1-10)
    int m_impact;                    // How much it affects life (1-10)
    bool m_resolved;                 // Whether it's been conquered
    std::vector<ActionStep> m_steps; // Breakdown into actionable tasks
};

#endif