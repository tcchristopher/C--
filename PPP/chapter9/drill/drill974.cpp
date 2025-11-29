#include "drill974.h"

Date::Date(int yy, Month mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
    if (int(mm) < 1 || int(mm) > 12) throw Invalid{};
    if (dd < 1 || dd > 31) throw Invalid{};
}

void Date::add_day(int n){
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

void Date::add_month(int n){
    int month_val = int(m) + n;
    while (month_val > 12){
        month_val -= 12;                    // This will keep cycling down 12 months, adding 1 year as a result until the excess months are done
        y++;
    }
    m = Month(month_val);
}

void Date::add_year(int n){
    y += n;
}

ostream& operator<<(ostream& os, const Date& d){
    // operator<< can call const member functions on const Date
    return os << '(' << d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
}

int main()
{
    try{
        Date today{1978, Month::Jun, 25};
        const Date immutable{2000, Month::Jan, 1};      // const Date

        Date tomorrow = today;
        tomorrow.add_day(1);

        cout << "today: " << today << '\n';
        cout << "tomorrow: " << tomorrow << '\n';

        // These work because year(), month(), day() are const:
        cout << "\nReading from const Date:\n";
        cout << "immutable year: " << immutable.year() << '\n';
        cout << "immutable month: " << int(immutable.month()) << '\n';
        cout << "immutable day: " << immutable.day() << '\n';

        // This would be a COMPILE ERROR
        // immutable.add_day(1);                           // Error: can't call non-const on const object

        // Test invalid date
        cout << "\nTesting invalid date:\n";
        Date bad{2004, Month(13), 5};
        cout << "This line never executes\n";
    }
    catch(Date::Invalid){
        cerr << "Error: Invalid date detected!\n";
    }

    return 0;
}