// Category enum and helpers

#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

enum class Category{
    INCOME,
    BILLS,
    FAMILY,
    HEALTH,
    WORK,
    HOUSING,
    RELATIONSHIPS,
    OTHER
};

// Helper function to convert Category to string
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

// Helper function to convert string to Category
inline Category string_to_category(const std::string& str) {
    if (str == "INCOME")                return Category::INCOME;
    if (str == "BILLS")                 return Category::BILLS;
    if (str == "FAMILY")                return Category::FAMILY;
    if (str == "HEALTH")                return Category::HEALTH;
    if (str == "WORK")                  return Category::WORK;
    if (str == "HOUSING")               return Category::HOUSING;
    if (str == "RELATIONSHIPS")         return Category::RELATIONSHIPS;
    return Category::OTHER;
}

#endif