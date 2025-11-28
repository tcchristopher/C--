#include "drill941.h"
#include "std_lib_facilities.h"

void init_day(Date& dd, int y, int m, int d)
{
    // simple validation (as per drill, ignore leap years)
    // Just check ranges

    if (m < 1 || m > 12){
        cerr << "Error: invalid month " << m << '\n';
        dd.y = 2001;
        dd.m = 1;
        dd.d = 1;
        return;
    }

    if (d < 1 || d > 31) {
        cerr << "Error: invalid day " << d << '\n';
        dd.y = 2001;
        dd.m = 1;
        dd.d = 1;
        return;
    }

    dd.y = y;
    dd.m = m;
    dd.d = d;
}

void add_day(Date& dd, int n)
{
    // simplified add n days
    dd.d += n;

    // add month overflow
    while (dd.d > 31){
        dd.d -= 31;
        dd.m++;
        if (dd.m > 12){
            dd.m = 1;
            dd.y++;
        }
    }
}

ostream& operator<<(ostream& os, const Date& d){
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
} 

int main()
{
    // Define today as June 25, 1978
    Date today;
    init_day(today, 1978, 6, 25);
    
    // Copy today into tomorrow and add one day
    Date tomorrow = today;
    add_day(tomorrow, 1);

    // Output both dates
    cout << "today: " << today << '\n';
    cout << "tomorrow: " << tomorrow << '\n';

    // Test with invalid date 
    cout << "\nTesting with invalid date (2004, 13, -5):\n";
    Date bad;
    init_day(bad, 2005, 13, -5);
    cout << "bad: " << bad << " (set to default after error)\n";

    return 0;
}