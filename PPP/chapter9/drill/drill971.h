#ifndef DRILL971_H
#define DRILL971_H

#include "std_lib_facilities.h"

enum class Month {
    Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

class Date {
    int y;
    Month m;
    int d;

public:
    class Invalid{ };

    Date(int y, Month m, int d);
    void add_day(int n);

    int year() const {return y;}
    Month month() const {return m;}
    int day() const{return d;}
};

std::ostream& operator<<(std::ostream& os, const Date& d);

#endif