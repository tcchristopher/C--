// Category enum and helpers
// Defines the Category enum for classifying anxiety items.
// Categories help users organise and filter their anxieties.

#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

// The eight categories an anxiety can belong to.
// OTHER is used as a catch-all for uncategorised items.

enum class Category{
    INCOME,         // Job, money, financial security
    BILLS,          // Payments, debts, financial obligations
    FAMILY,         // Family relationships and responsibilities
    HEALTH,         // Physical and mental health concerns
    WORK,           // Job tasks, career, professional issues
    HOUSING,        // Living situation, rent, home maintenance
    RELATIONSHIPS,  // Friendships, romantic relationships, social
    OTHER           // Anything that doesn't fit above
};

// HELPER FUNCTIONS

// Converts a Category enum value to its string representation.
// Used for display and file persistence.
// Returns "UNKNOWN" if given an invalid category (shouldn't happen).
inline std::string category_to_string(Category cat) {
    switch (cat) {
        case Category::INCOME:          return "INCOME";
        case Category::BILLS:           return "BILLS";
        case Category::FAMILY:          return "FAMILY";
        case Category::HEALTH:          return "HEALTH";
        case Category::WORK:            return "WORK";
        case Category::HOUSING:         return "HOUSING";
        case Category::RELATIONSHIPS:   return "OTHER";
        default:                        return "UNKNOWN";
    }
}

// Converts a string to its Category enum value.
// Used when loading from file.
// Returns OTHER if the string doesn't match any category.
inline Category string_to_category(const std::string& str) {
    if (str == "INCOME")                return Category::INCOME;
    if (str == "BILLS")                 return Category::BILLS;
    if (str == "FAMILY")                return Category::FAMILY;
    if (str == "HEALTH")                return Category::HEALTH;
    if (str == "WORK")                  return Category::WORK;
    if (str == "HOUSING")               return Category::HOUSING;
    if (str == "RELATIONSHIPS")         return Category::RELATIONSHIPS;
    return Category::OTHER;         // Default for unknown strings
}

#endif