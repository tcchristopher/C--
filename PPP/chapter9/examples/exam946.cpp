// Evolving a class - Reporting errors in a Date class
#include "std_lib_facilities.h"
#include <iostream>

// simple Date (prevent invalid dates)
class Date {
public:
    class Invalid {};                           // to be used as exception
    Date(int y, int m, int d);                  // constructor: check for valid date and initialize
    void add_day(int n);                        // increase the Date by n days
    int month() {return m; }
    int day() {return d; }
    int year() {return y; }
private:
    int y, m, d;                                // year, month, day
    bool is_valid();                            // return true if date is valid
};

Date::Date(int yy, int mm, int dd)              // constructor
    :y{yy}, m{mm}, d{dd}                        // note: member initializers in notation form, could also be written as y = yy; etc.
{
    if (!is_valid()) throw Invalid{};           // check for validity
}

bool Date::is_valid()                           // return true if date is valid
{
    if (m<1 || 12<m) return false;
    if (d<1 || 31<m) return false;
    if (y<0) return false;
    // ...
}

void Date::add_day(int n)
{
    // ...
}

void f(int x, int y)
try{
    Date dxy {2004, x, y};
    // cout << dxy << '\n';
dxy.add_day(2);
}
catch (Date::Invalid){
    error("invalid date");
}

int main()
{

}