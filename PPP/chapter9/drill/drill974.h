#ifndef DRILL974_H
#define DRILL974_H

#include "std_lib_facilities.h"

enum class Month {
    Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

class Date {
    int y;
    Month m;
    int d;

public:
    class Invalid { };

    Date(int y, Month m, int d);

    // const member functions, they won't modify as a result
    int year() const { return y; }
    Month month() const { return m; }
    int day() const { return d; }

    // non-const member functions, they will modify
    void add_day(int n);
    void add_month(int n);
    void add_year(int n);
};

std::ostream& operator<<(std::ostream& os, const Date& d);

#endif