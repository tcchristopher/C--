# Chapter 9 Date Drill - Complete & Corrected Walkthrough
## Accurate to Stroustrup PPP 2nd Edition Chapter 9

---

## The Drill Instructions (Page 338)

"This drill simply involves getting the sequence of versions of Date to work. For each version define a Date called today initialized to June 25, 1978. Then, define a Date called tomorrow and give it a value by copying today into it and increasing its day by one using add_day(). Finally, output today and tomorrow using a << defined as in §9.8.

Your check for a valid date may be very simple. Feel free to ignore leap years. However, don't accept a month that is not in the [1,12] range or day of the month that is not in the [1,31] range. Test each version with at least one invalid date (e.g., 2004, 13, –5).

1. The version from §9.4.1
2. The version from §9.4.2
3. The version from §9.4.3
4. The version from §9.7.1
5. The version from §9.7.4"

---

## The Evolution Path

### What Each Version Teaches

| Version | Section | Key Concept | Error Handling |
|---------|---------|-------------|----------------|
| 1 | §9.4.1 | struct + helper functions | Simple checks |
| 2 | §9.4.2 | Constructor + member functions | Simple checks |
| 3 | §9.4.3 | Private members + exceptions | **Exceptions (§9.4.6)** |
| 4 | §9.7.1 | Month enum (type safety) | Exceptions |
| 5 | §9.7.4 | const member functions | Exceptions |

**Critical Note:** Starting with Version 3, we use the exception handling technique from §9.4.6 (pages 317-318).

---

## Version 1: §9.4.1 - struct and functions (Page 308-310)

### What Stroustrup Shows

From page 308:
```cpp
// simple Date (too simple?)
struct Date {
    int y; // year
    int m; // month in year
    int d; // day of month
};
```

From page 309-310:
```cpp
void init_day(Date& dd, int y, int m, int d)
{
    // check that (y,m,d) is a valid date
    // if it is, use it to initialize dd
}

void add_day(Date& dd, int n)
{
    // increase dd by n days
}
```

### The Philosophy

This is the "C-style" approach: data structure + functions that operate on it. No protection, no guarantees.

### Your Implementation

**date1.h:**
```cpp
#ifndef DATE1_H
#define DATE1_H

#include <iostream>

struct Date {
    int y;  // year
    int m;  // month
    int d;  // day
};

// Helper functions
void init_day(Date& dd, int y, int m, int d);
void add_day(Date& dd, int n);

// Output operator (as in §9.8)
std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
```

**date1.cpp:**
```cpp
#include "date1.h"
#include <iostream>

using namespace std;

void init_day(Date& dd, int y, int m, int d) {
    // Simple validation (as per drill: ignore leap years)
    // Just check ranges - not using exceptions yet
    if (m < 1 || m > 12) {
        cerr << "Error: Invalid month " << m << '\n';
        // In real code, we'd handle this better, but Version 1 is deliberately simple
        dd.y = 2001;
        dd.m = 1;
        dd.d = 1;
        return;
    }
    if (d < 1 || d > 31) {
        cerr << "Error: Invalid day " << d << '\n';
        dd.y = 2001;
        dd.m = 1;
        dd.d = 1;
        return;
    }
    
    dd.y = y;
    dd.m = m;
    dd.d = d;
}

void add_day(Date& dd, int n) {
    // Simplified: just add n days
    dd.d += n;
    
    // Handle month overflow (simplified, ignoring actual month lengths)
    while (dd.d > 31) {
        dd.d -= 31;
        dd.m++;
        if (dd.m > 12) {
            dd.m = 1;
            dd.y++;
        }
    }
}

ostream& operator<<(ostream& os, const Date& d) {
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}
```

**main1.cpp:**
```cpp
#include "date1.h"
#include <iostream>

using namespace std;

int main() {
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
    cout << "\nTesting invalid date (2004, 13, -5):\n";
    Date bad;
    init_day(bad, 2004, 13, -5);
    cout << "bad: " << bad << " (set to default after error)\n";
    
    return 0;
}
```

**Compile:**
```bash
g++ -std=c++17 -Wall -Wextra -o date1 main1.cpp date1.cpp
./date1
```

**Expected output:**
```
today: (1978,6,25)
tomorrow: (1978,6,26)

Testing invalid date (2004, 13, -5):
Error: Invalid month 13
bad: (2001,1,1) (set to default after error)
```

### The Problem

```cpp
Date birthday {1960,12,31};
++birthday.d;  // Disaster! Now (1960,12,32) - invalid
```

Nothing stops you from corrupting the data after initialization.

---

## Version 2: §9.4.2 - Member functions and constructors (Page 310-312)

### What Stroustrup Shows

From page 311:
```cpp
struct Date {
    int y, m, d;
    Date(int y, int m, int d); // constructor
    void add_day(int n);
};
```

Key innovation: **Constructor ensures initialization**. You can't forget to initialize.

### Your Implementation

**date2.h:**
```cpp
#ifndef DATE2_H
#define DATE2_H

#include <iostream>

struct Date {
    int y, m, d;
    
    Date(int y, int m, int d);  // Constructor
    void add_day(int n);         // Member function
};

std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
```

**date2.cpp:**
```cpp
#include "date2.h"
#include <iostream>

using namespace std;

Date::Date(int yy, int mm, int dd) {
    // Validate - still simple, no exceptions yet
    if (mm < 1 || mm > 12) {
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
    
    while (d > 31) {
        d -= 31;
        m++;
        if (m > 12) {
            m = 1;
            y++;
        }
    }
}

ostream& operator<<(ostream& os, const Date& d) {
    return os << '(' << d.y << ',' << d.m << ',' << d.d << ')';
}
```

**main2.cpp:**
```cpp
#include "date2.h"
#include <iostream>

using namespace std;

int main() {
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
    cout << "bad: " << bad << " (set to default after error)\n";
    
    return 0;
}
```

**Compile:**
```bash
g++ -std=c++17 -Wall -Wextra -o date2 main2.cpp date2.cpp
./date2
```

### The Remaining Problem

```cpp
Date birthday(1970, 12, 30);
birthday.m = 14;  // Still possible! m is public!
```

Constructor ensures valid *initialization*, but data can still be corrupted afterward.

---

## Version 3: §9.4.3 - Keep details private (Page 312-313 + §9.4.6 for exceptions)

### What Stroustrup Shows

From page 313:
```cpp
class Date {
    int y, m, d;  // now PRIVATE
public:
    Date(int y, int m, int d);
    void add_day(int n);
    int month() { return m; }
    int day() { return d; }
    int year() { return y; }
};
```

From page 317-318 (§9.4.6 - Reporting errors):
```cpp
class Date {
public:
    class Invalid { }; // to be used as exception
    Date(int y, int m, int d);
    // ...
};

Date::Date(int yy, int mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
    if (!is_valid()) throw Invalid{};
}
```

**This is where we start using exceptions!**

### Your Implementation

**date3.h:**
```cpp
#ifndef DATE3_H
#define DATE3_H

#include <iostream>

class Date {
    int y, m, d;  // PRIVATE by default in a class
    
public:
    class Invalid { };  // Exception type (§9.4.6)
    
    Date(int y, int m, int d);
    void add_day(int n);
    
    // Accessors (getters)
    int year() const { return y; }
    int month() const { return m; }
    int day() const { return d; }
};

std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
```

**date3.cpp:**
```cpp
#include "date3.h"
#include <iostream>

using namespace std;

Date::Date(int yy, int mm, int dd)
    : y{yy}, m{mm}, d{dd}  // Member initializer list (§9.4.4)
{
    // Validate using exceptions (§9.4.6)
    if (mm < 1 || mm > 12) throw Invalid{};
    if (dd < 1 || dd > 31) throw Invalid{};
}

void Date::add_day(int n) {
    d += n;
    
    while (d > 31) {
        d -= 31;
        m++;
        if (m > 12) {
            m = 1;
            y++;
        }
    }
}

ostream& operator<<(ostream& os, const Date& d) {
    // Must use accessors since members are private
    return os << '(' << d.year() << ',' << d.month() << ',' << d.day() << ')';
}
```

**main3.cpp:**
```cpp
#include "date3.h"
#include <iostream>

using namespace std;

int main() {
    try {
        Date today(1978, 6, 25);
        
        Date tomorrow = today;
        tomorrow.add_day(1);
        
        cout << "today: " << today << '\n';
        cout << "tomorrow: " << tomorrow << '\n';
        
        // This is now IMPOSSIBLE:
        // today.m = 14;  // Compile error! m is private
        
        // Test invalid date - will throw exception
        cout << "\nTesting invalid date (2004, 13, -5):\n";
        Date bad(2004, 13, -5);
        cout << "This line never executes\n";
    }
    catch(Date::Invalid) {
        cerr << "Error: Invalid date detected!\n";
    }
    
    return 0;
}
```

**Compile:**
```bash
g++ -std=c++17 -Wall -Wextra -o date3 main3.cpp date3.cpp
./date3
```

**Expected output:**
```
today: (1978,6,25)
tomorrow: (1978,6,26)

Testing invalid date (2004, 13, -5):
Error: Invalid date detected!
```

### Victory!

Now it's **impossible** to create an invalid Date. The compiler prevents direct access, and the constructor throws an exception if you try to initialize with invalid values.

---

## Version 4: §9.7.1 - Argument types (Page 324-325)

### What Stroustrup Shows

From pages 318-319:
```cpp
enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
```

From page 324:
```cpp
class Date {
public:
    Date(int y, Month m, int d);
    // ...
private:
    int y;
    Month m;
    int d;
};
```

Key quote (page 324): "When we use a Month type, the compiler will catch us if we swap month and day."

### Why This Matters

The problem: `Date(1998, 4, 3)`
- Is that April 3 or March 4?
- US: month/day | Europe: day/month

Solution: `Date(1998, Month::apr, 3)` - **unambiguous**

### Your Implementation

**date4.h:**
```cpp
#ifndef DATE4_H
#define DATE4_H

#include <iostream>

enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
    int y;
    Month m;
    int d;
    
public:
    class Invalid { };
    
    Date(int y, Month m, int d);
    void add_day(int n);
    
    int year() const { return y; }
    Month month() const { return m; }
    int day() const { return d; }
};

std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
```

**date4.cpp:**
```cpp
#include "date4.h"
#include <iostream>

using namespace std;

Date::Date(int yy, Month mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
    // Validate
    if (int(mm) < 1 || int(mm) > 12) throw Invalid{};
    if (dd < 1 || dd > 31) throw Invalid{};
}

void Date::add_day(int n) {
    d += n;
    
    while (d > 31) {
        d -= 31;
        int month_val = int(m) + 1;
        if (month_val > 12) {
            month_val = 1;
            y++;
        }
        m = Month(month_val);
    }
}

ostream& operator<<(ostream& os, const Date& d) {
    return os << '(' << d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
}
```

**main4.cpp:**
```cpp
#include "date4.h"
#include <iostream>

using namespace std;

int main() {
    try {
        // Now completely unambiguous!
        Date today{1978, Month::jun, 25};
        
        Date tomorrow = today;
        tomorrow.add_day(1);
        
        cout << "today: " << today << '\n';
        cout << "tomorrow: " << tomorrow << '\n';
        
        // These are now COMPILE ERRORS (try uncommenting):
        // Date d1{1998, 4, 3};  // Error: 4 is not a Month
        // Date d2{4, Month::mar, 1998};  // Error: wrong type order
        
        // Test invalid month value using unsafe cast
        cout << "\nTesting invalid month (Month(13)):\n";
        Date bad{2004, Month(13), 5};
        cout << "This line never executes\n";
    }
    catch(Date::Invalid) {
        cerr << "Error: Invalid date detected!\n";
    }
    
    return 0;
}
```

**Compile:**
```bash
g++ -std=c++17 -Wall -Wextra -o date4 main4.cpp date4.cpp
./date4
```

**Expected output:**
```
today: (1978,6,25)
tomorrow: (1978,6,26)

Testing invalid month (Month(13)):
Error: Invalid date detected!
```

### The Power of Type Safety

```cpp
Date dx1{1998, 4, 3};  // COMPILE ERROR: 4 is not a Month
Date dx2{4, Month::mar, 1998};  // COMPILE ERROR: 4 is not int at position 0
Date dx3{1998, Month::mar, 30};  // ✅ OK - clear and unambiguous
```

The compiler becomes your friend.

---

## Version 5: §9.7.4 - const member functions (Page 330-331)

### What Stroustrup Shows

From page 331:
```cpp
class Date {
public:
    int day() const;     // const member: can't modify
    Month month() const;
    int year() const;
    
    void add_day(int n);     // non-const: can modify
    void add_month(int n);
    void add_year(int n);
private:
    int y;
    Month m;
    int d;
};
```

Key concept: Distinguish operations that **read** from operations that **modify**.

### Why const Matters

```cpp
void some_function(Date& d, const Date& start_of_term) {
    d.add_day(3);                    // ✅ OK: d is mutable
    start_of_term.add_day(3);        // ❌ ERROR: can't modify const
    
    cout << d.day();                 // ✅ OK if day() is const
    cout << start_of_term.day();     // ✅ ONLY works if day() is const
}
```

Without `const` on `day()`, you couldn't call it on `const Date` objects.

### Your Implementation

**date5.h:**
```cpp
#ifndef DATE5_H
#define DATE5_H

#include <iostream>

enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
    int y;
    Month m;
    int d;
    
public:
    class Invalid { };
    
    Date(int y, Month m, int d);
    
    // const member functions - promise not to modify
    int year() const { return y; }
    Month month() const { return m; }
    int day() const { return d; }
    
    // non-const member functions - can modify
    void add_day(int n);
    void add_month(int n);
    void add_year(int n);
};

std::ostream& operator<<(std::ostream& os, const Date& d);

#endif
```

**date5.cpp:**
```cpp
#include "date5.h"
#include <iostream>

using namespace std;

Date::Date(int yy, Month mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
    if (int(mm) < 1 || int(mm) > 12) throw Invalid{};
    if (dd < 1 || dd > 31) throw Invalid{};
}

void Date::add_day(int n) {
    d += n;
    
    while (d > 31) {
        d -= 31;
        int month_val = int(m) + 1;
        if (month_val > 12) {
            month_val = 1;
            y++;
        }
        m = Month(month_val);
    }
}

void Date::add_month(int n) {
    int month_val = int(m) + n;
    while (month_val > 12) {
        month_val -= 12;
        y++;
    }
    m = Month(month_val);
}

void Date::add_year(int n) {
    y += n;
}

ostream& operator<<(ostream& os, const Date& d) {
    // operator<< can call const member functions on const Date
    return os << '(' << d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
}
```

**main5.cpp:**
```cpp
#include "date5.h"
#include <iostream>

using namespace std;

int main() {
    try {
        Date today{1978, Month::jun, 25};
        const Date immutable{2000, Month::jan, 1};  // const Date
        
        Date tomorrow = today;
        tomorrow.add_day(1);
        
        cout << "today: " << today << '\n';
        cout << "tomorrow: " << tomorrow << '\n';
        
        // These work because year(), month(), day() are const:
        cout << "\nReading from const Date:\n";
        cout << "immutable year: " << immutable.year() << '\n';
        cout << "immutable month: " << int(immutable.month()) << '\n';
        cout << "immutable day: " << immutable.day() << '\n';
        
        // This would be a COMPILE ERROR (try uncommenting):
        // immutable.add_day(1);  // Error: can't call non-const on const object
        
        // Test invalid date
        cout << "\nTesting invalid date:\n";
        Date bad{2004, Month(13), 5};
        cout << "This line never executes\n";
    }
    catch(Date::Invalid) {
        cerr << "Error: Invalid date detected!\n";
    }
    
    return 0;
}
```

**Compile:**
```bash
g++ -std=c++17 -Wall -Wextra -o date5 main5.cpp date5.cpp
./date5
```

**Expected output:**
```
today: (1978,6,25)
tomorrow: (1978,6,26)

Reading from const Date:
immutable year: 2000
immutable month: 1
immutable day: 1

Testing invalid date:
Error: Invalid date detected!
```

### The const Contract

```cpp
int Date::day() const {
    ++d;  // ❌ COMPILE ERROR: can't modify in const function
    return d;
}
```

The `const` after the parameter list is a **promise** that the function won't modify the object. The compiler enforces this.

---

## Complete Project Structure

```
chapter9_drill/
├── version1/
│   ├── date1.h
│   ├── date1.cpp
│   └── main1.cpp
├── version2/
│   ├── date2.h
│   ├── date2.cpp
│   └── main2.cpp
├── version3/
│   ├── date3.h
│   ├── date3.cpp
│   └── main3.cpp
├── version4/
│   ├── date4.h
│   ├── date4.cpp
│   └── main4.cpp
└── version5/
    ├── date5.h
    ├── date5.cpp
    └── main5.cpp
```

---

## Compilation Commands

```bash
# Version 1
cd version1
g++ -std=c++17 -Wall -Wextra -o date1 main1.cpp date1.cpp
./date1

# Version 2
cd ../version2
g++ -std=c++17 -Wall -Wextra -o date2 main2.cpp date2.cpp
./date2

# Version 3 (first use of exceptions)
cd ../version3
g++ -std=c++17 -Wall -Wextra -o date3 main3.cpp date3.cpp
./date3

# Version 4 (Month enum)
cd ../version4
g++ -std=c++17 -Wall -Wextra -o date4 main4.cpp date4.cpp
./date4

# Version 5 (const correctness)
cd ../version5
g++ -std=c++17 -Wall -Wextra -o date5 main5.cpp date5.cpp
./date5
```

---

## The Evolution Summary

### What Each Version Teaches

| Version | Concept | Protection Level | Error Handling |
|---------|---------|------------------|----------------|
| 1 | Helper functions | None | Simple messages |
| 2 | Constructor | Initialization only | Simple messages |
| 3 | **Encapsulation** | Complete | **Exceptions** |
| 4 | Type safety | Complete + compile-time checks | Exceptions |
| 5 | const correctness | Complete + const checking | Exceptions |

### The Invariant Evolution

**Invariant for Date:** "A Date must represent a valid day (month ∈ [1,12], day ∈ [1,31])"

- **Version 1**: Invariant can be violated anytime (`d.m = 99`)
- **Version 2**: Invariant holds at construction, can be violated after
- **Version 3-5**: Invariant is **mathematically impossible** to violate

### Key Quotes from Stroustrup

**On constructors (page 311):**
> "A member function with the same name as its class is special. It is called a constructor and will be used for initialization."

**On encapsulation (page 313):**
> "As long as we leave the representation of Date accessible to everybody, somebody will — by accident or design — mess it up."

**On exceptions (page 317):**
> "What do we do when we find an invalid date? From §5.6, we know that the answer to the first question is 'Throw an exception.'"

**On const (page 331):**
> "We use const right after the argument list in a member function declaration to indicate that the member function can be called for a const object."

**On type safety (page 324):**
> "When we use a Month type, the compiler will catch us if we swap month and day."

---

## Exception Handling Deep Dive

### Why Exceptions from Version 3 Onward?

Stroustrup explicitly introduces exceptions in §9.4.6 (pages 317-318) after discussing private members. This is the professional way to handle errors:

**Bad (what we don't do):**
```cpp
if (mm < 1 || mm > 12) {
    exit(1);  // ❌ Kills the entire program
}
```

**Good (what Stroustrup teaches):**
```cpp
if (mm < 1 || mm > 12) {
    throw Invalid{};  // ✅ Caller can catch and recover
}
```

### Exception Usage Pattern

```cpp
// Define exception type inside the class
class Date {
public:
    class Invalid { };  // Exception class
    // ...
};

// Throw when validation fails
Date::Date(int yy, Month mm, int dd)
    : y{yy}, m{mm}, d{dd}
{
    if (int(mm) < 1 || int(mm) > 12) throw Invalid{};
    if (dd < 1 || dd > 31) throw Invalid{};
}

// Catch in client code
try {
    Date d{2004, Month(13), 5};
}
catch(Date::Invalid) {
    cerr << "Invalid date!\n";
}
```

---

## Testing Strategy

### For Each Version

**Basic functionality:**
```cpp
Date today{1978, Month::jun, 25};
Date tomorrow = today;
tomorrow.add_day(1);
cout << today << " " << tomorrow << '\n';
```

**Invalid dates (should error):**

Version 1-2:
```cpp
Date bad1{2024, 0, 15};    // Month too low
Date bad2{2024, 13, 15};   // Month too high
Date bad3{2024, 6, 0};     // Day too low
Date bad4{2024, 6, 32};    // Day too high
```

Version 3-5 (catch exceptions):
```cpp
try {
    Date bad{2004, Month(13), -5};
}
catch(Date::Invalid) {
    cerr << "Caught invalid date\n";
}
```

---

## Common Mistakes to Avoid

### 1. Forgetting exception handling in Version 3+

**Wrong:**
```cpp
int main() {
    Date bad{2004, Month(13), 5};  // Uncaught exception = crash
    return 0;
}
```

**Right:**
```cpp
int main() {
    try {
        Date bad{2004, Month(13), 5};
    }
    catch(Date::Invalid) {
        cerr << "Invalid date\n";
    }
    return 0;
}
```

### 2. Accessing private members in operator<<

**Wrong (Version 3+):**
```cpp
ostream& operator<<(ostream& os, const Date& d) {
    return os << d.y;  // ❌ Error: y is private!
}
```

**Right:**
```cpp
ostream& operator<<(ostream& os, const Date& d) {
    return os << d.year();  // ✅ Use accessor
}
```

### 3. Forgetting const on getters (Version 5)

**Wrong:**
```cpp
class Date {
public:
    int year() { return y; }  // ❌ Missing const
};

void f(const Date& d) {
    cout << d.year();  // ❌ Error: can't call non-const on const
}
```

**Right:**
```cpp
class Date {
public:
    int year() const { return y; }  // ✅ const member
};
```

### 4. Wrong Month enum syntax (Version 4-5)

**Wrong:**
```cpp
Date d{1978, jun, 25};     // ❌ jun not in scope
Date d{1978, 6, 25};       // ❌ 6 is not a Month
```

**Right:**
```cpp
Date d{1978, Month::jun, 25};  // ✅ Correct
```

---

## What You've Learned

By completing this drill, you now understand:

1. **Why constructors matter** - Can't forget initialization
2. **Why encapsulation matters** - Invalid states become impossible
3. **Why exceptions matter** - Caller can recover from errors
4. **Why type safety matters** - Compiler catches logical errors
5. **Why const matters** - Distinguishes queries from commands

This is the foundation of professional C++ programming.

---

## Final Checklist

- [ ] Version 1: struct + helper functions (simple validation)
- [ ] Version 2: Constructor + member function (simple validation)
- [ ] Version 3: Private members + exceptions (§9.4.6)
- [ ] Version 4: Month enum (§9.7.1)
- [ ] Version 5: const member functions (§9.7.4)
- [ ] All code compiles without warnings
- [ ] All versions test with June 25, 1978
- [ ] All versions test invalid date (2004, 13, -5 or similar)
- [ ] Versions 3-5 use try-catch for invalid dates

---

## Next Steps for Your Sobriety Counter

Apply these same principles:

```cpp
class Counter {
    string name;        // Can't be empty (invariant)
    time_t start_time;  // Can't be in future (invariant)
    
public:
    class Invalid { };  // Exception type
    
    Counter(const string& n, time_t t);
    
    // const - queries only
    string getName() const { return name; }
    int getDaysClean() const;
    
    // non-const - commands
    void reset();
};
```

You now know exactly how to build a robust, self-protecting class.

Now go implement it. Type every line. Feel the evolution. This is mastery.
