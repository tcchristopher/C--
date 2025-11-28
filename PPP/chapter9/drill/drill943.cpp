#include "drill943.h"
#include "std_lib_facilities.h"

Date::Date(int yy, int mm, int dd)
    :y{yy}, m{mm}, d{dd}            //Member initializer list
{
    // Validate using exceptions
    if (mm < 1 || mm > 12) throw Invalid{};
    if (dd < 1 || dd > 31) throw Invalid{};
}

void Date::add_day(int n){
    d += n;

    while (d > 31){
        d -= 31;
        m++;
        if (m > 12){
            m = 1;
            y++;
        }
    }
}

ostream& operator<<(ostream& os, const Date& d) {
    // Must use accessors because the members are private
    return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << '\n';
}

int main() {
    try {
        Date today(1978, 6, 25);
        
        Date tomorrow = today;
        tomorrow.add_day(1);

        cout << "today: " << today << '\n';
        cout << "tomorrow: " << tomorrow << '\n';


        // Test invalid date - exception will be thrown
        cout << "\nTesting invalid date (2004, 13, -5):\n";
        Date bad(2004, 13, -5);
        cout << "This line never executes\n";
    }
    catch (Date::Invalid) {
        cerr << "Error: Invalid date detected!\n";
    }

    return 0;
}