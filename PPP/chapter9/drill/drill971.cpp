#include "drill971.h"
#include "std_lib_facilities.h"

Date::Date(int yy, Month mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
    // Validate
    if (int(mm) < 1 || int(mm) > 12) throw Invalid{};
    if (dd < 1 || dd > 31) throw Invalid{};
}

void Date::add_day(int n)
{
    d += n;

    while (d > 31){
        d -= 31;
        int month_val = int(m) + 1;
        if (month_val > 12){
            month_val = 1;
            y++;
        }
        m = Month(month_val);
    }
}

ostream& operator<<(ostream& os, const Date& d){
    return os << '(' << d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
}


int main()
{
    try{
        // Now completely unambiguous!
        Date today{1978, Month::Jun, 25};

        Date tomorrow = today;
        tomorrow.add_day(1);

        cout << "today: " << today << '\n';
        cout << "tomorrow: " << tomorrow << '\n';

        // These are compile errors
        // Date d1{1998, 4, 3};                    // Error: 4 is not a Month
        // Date d2{4, Month::Mar, 1998};           // Error: wrong type order

        // Test invalid month using unsafe cast
        cout << "\nTesting invalid month (Month(13)):\n";
        Date bad{2004, Month(13), 5};
        cout << "This line never executes\n";       
    }
    catch(Date::Invalid){
        cerr << "Error: Invalid date detected!\n";
    }

    return 0;

}