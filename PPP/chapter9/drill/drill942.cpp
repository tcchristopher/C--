#include "drill942.h"
#include "std_lib_facilities.h"

Date::Date(int yy, int mm, int dd){
    // Validate - still simple, no exceptions yet
    if (mm < 1 || mm > 12){
        cerr << "Error: Invalid month " << mm << '\n';
        y = 2001; m = 1; d = 1;
        return;
    }
    if (dd < 1 || dd > 31) {
        cerr << "Error: Invalid day " << dd << '\n';
        y = 2001; m = 1; d = 1;
        return;     
    }

    y = yy;
    m = mm;
    d = dd;
}

void Date::add_day(int n) {
    d += n;

    while (d > 32) {
        d -= 31;
        m++;
        if (m > 12){
            m = 1;
            y++;
        }
    }
}

ostream& operator<<(ostream& os, const Date& d){
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}

int main()
{
    // Constructor ensures valid initialization
    Date today(1978, 6, 25);

    // Copy and increment
    Date tomorrow = today;
    tomorrow.add_day(1);

    cout << "today: " << today << '\n';
    cout << "tomorrow: " << tomorrow << '\n';

    // Test invalid date
    cout << "\nTesting invalid date (2004, 13, -5):\n";
    Date bad(2004, 13, -5);
    cout << "bad: " << bad << " (set to detault after error)\n";

    return 0;
}