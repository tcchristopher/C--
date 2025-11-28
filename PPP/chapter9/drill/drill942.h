#ifndef DRILL942_H
#define DRILL942_H

#include "std_lib_facilities.h"

struct Date {
    int y, m , d;
    Date(int y, int m , int d);     // constructor
    void add_day(int n);            // member function
};


std::ostream& operator<<(std::ostream& os, const Date& d);

#endif