// Evolving a class - Defining member functions of a Date class
#include "std_lib_facilities.h"

// simple Date (some people prefer implementation details last)
class Date {
public:
    Date(int y, int m, int d);                  // constructor: check for valid date and initialize
    void add_day(int n);                        // increase the Date by n days
    int month() {return m; }
    int day() {return d; }
    int year() {return y; }
private:
    int y, m, d;                                // year, month, day
};

Date::Date(int yy, int mm, int dd)              // constructor
    :y{yy}, m{mm}, d{dd}                        // note: member initializers in notation form, could also be written as y = yy; etc.
{
}

void Date::add_day(int n)
{
    // ...
}



int main()
{

}