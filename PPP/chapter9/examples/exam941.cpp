// Evolving a class - Structs and functions through a Date class
#include "std_lib_facilities.h"

// Simple Date (too simple?)
struct Date {
    int y;              // year
    int m;              // month of the year
    int d;              // day of the month
};

// Date today;             // a Date variable (a named object)

// helper functions for Date

void init_day(Date& dd, int y, int m, int d)
{
    // check that (y,m,d) is a valid date
    // if it is, use it to initialize dd
}

void add_day(Date& dd, int n)
{
    // increase dd by n days
}

void f()
{
    Date today;
    // init_day(today, 12, 24, 2005);      // ERROR: the date has been entered incorrectly vs arguments for function
    init_day(today, 2005, 12, 24);      // corrected
    add_day(today, 1);
}

int main()
{
    // // set today to December 24, 2005
    // today.y = 2005;
    // today.m = 24;
    // today.d = 12;

}