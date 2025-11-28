#ifndef DRILL943_H
#define DRILL943_H

#include "std_lib_facilities.h"

class Date {
    int y, m, d;                // Private by default in a class

public:
    class Invalid { };          // Exception type

    Date(int y, int m, int d);
    void add_day(int n);

    // Accessors (getters)
    int year() const {return y;}
    int month() const {return m;}
    int day() const {return d;}
};

std::ostream& operator<<(std::ostream& os, const Date& d);

#endif