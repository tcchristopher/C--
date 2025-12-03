// AnxietyList class headers

#ifndef ANXIETY_LIST_H
#define ANXIETY_LIST_H

#include <vector>
#include <string>
#include "anxiety_item.h"

class AnxietyList {
public:
    // Constructor
    AnxietyList();

    // Core operations
    void add(const AnxietyItem& item);
    void remove(int index);
    AnxietyItem& get(int index);
    const AnxietyItem& get(int index) const;
    int size() const;

    // Filtered access
    std::vector<AnxietyItem*> get_active();
    std::vector<AnxietyItem*> get_resolved();

    // Sorting
    void sort_by_priority();

    // File Persistence for saving data from the user
    bool save(const std::string& filename) const;
    bool load(const std::string& filename);

    // Stats
    int active_count() const;
    int resolved_count() const;
    int total_steps_completed() const;

private:
    std::vector<AnxietyItem> m_items;
};

#endif