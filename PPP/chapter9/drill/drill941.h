#ifndef DRILL941_H
#define DRILL941_H

#include "std_lib_facilities.h"

struct Date {
    int y;              // year
    int m;              // month
    int d;              // day
};

// helper functions
void init_day(Date& dd, int y, int m, int d);
void add_day(Date& dd, int n);

// Output operator
std::ostream& operator<<(std::ostream& os, const Date& d);

#endif