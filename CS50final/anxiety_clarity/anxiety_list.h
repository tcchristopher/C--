// Defines the AnxietyList class - manages the collection of all anxiety items.
// Handles adding, removing, sorting, filtering, and file persistence.

#ifndef ANXIETY_LIST_H
#define ANXIETY_LIST_H

#include <vector>
#include <string>
#include "anxiety_item.h"

class AnxietyList {
public:
    // CONSTRUCTOR
    
    // Creates an empty anxiety list.
    AnxietyList();
    
    // CORE OPERATIONS
    
    // Adds a new anxiety item to the list.
    void add(const AnxietyItem& item);
    
    // Removes the anxiety at the given index.
    // Does nothing if index is out of range.
    void remove(int index);
    
    // Returns a modifiable reference to the anxiety at index.
    // Throws std::out_of_range if index is invalid.
    AnxietyItem& get(int index);
    
    // Returns a read-only reference to the anxiety at index.
    // Throws std::out_of_range if index is invalid.
    const AnxietyItem& get(int index) const;
    
    // Returns the total number of anxiety items.
    int size() const;
    
    // FILTERED ACCESS
    // These return pointers to allow modification of original items.
    
    // Returns pointers to all unresolved anxieties.
    std::vector<AnxietyItem*> get_active();
    
    // Returns pointers to all resolved anxieties.
    std::vector<AnxietyItem*> get_resolved();
    
    // SORTING
    
    // Sorts the list by priority (highest first).
    // Unresolved items always come before resolved items.
    void sort_by_priority();
    
    // FILE PERSISTENCE
    
    // Saves all anxieties and steps to a text file.
    // Returns true on success, false on failure.
    bool save(const std::string& filename) const;
    
    // Loads anxieties and steps from a text file.
    // Clears existing data before loading.
    // Skips corrupted lines but continues loading.
    // Returns true if file was opened, false otherwise.
    bool load(const std::string& filename);
    
    // STATISTICS
    
    // Returns count of unresolved anxieties.
    int active_count() const;
    
    // Returns count of resolved anxieties.
    int resolved_count() const;
    
    // Returns total completed steps across all anxieties.
    int total_steps_completed() const;
    
private:
    std::vector<AnxietyItem> m_items;  // All anxiety items
};

#endif