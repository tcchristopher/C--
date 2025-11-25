// Evolving a class - Adding member functions to a Date class
#include "std_lib_facilities.h"

// simple Date
// guarantee initialization with constructor
// provide some notational convenience
struct Date {
    int y,m,d;                          // year, month, day
    Date(int y, int m, int d);          // check for valid date and initialize
    void add_day(int n);                // increase the Date by n days
};

Date last {2000, 12, 31};

int main()
{
    last.add_day(1);
}