// Evolving a class - Operator overloading in a Date class
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

enum class Month{
    Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
};

Month int_to_month (int x)
{
    if (x<int(Month::Jan) || int(Month::Dec)<x) error("bad month");
    return Month(x);
}

// operator overloading
Month operator++(Month& m)                      // prefix increment operator
{
    m = (m==Month::Dec) ? Month::Jan : Month(int(m)+1); //"Wrap around"
    return m;
}

vector<string> month_tbl;

ostream& operator<<(ostream& os, Month m)
{
    return os << month_tbl[int(m)];
}


enum class Day{
    monday = 1, tuesday, wednesday, thursday, friday, saturday, sunday
};

// functions
void f(int x, int y)
try{
    Date dxy {2004, x, y};
    // cout << dxy << '\n';
dxy.add_day(2);
}
catch (Date::Invalid){
    error("invalid date");
}

void g(int m)
{
    Month mm = int_to_month(m);
    // ...
}

int main()
{

}