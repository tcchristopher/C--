// Variable clean up

// The road to the final version of the full Calculator
#include "std_lib_facilities.h"


// Constants for the code
const char number = '8';                        // t.kind == number means that t is a number token
const char quit = 'q';
const char print = ';';
const string prompt = "> ";
const string result = "= ";
const char name = 'a';                          // name token
const char let = 'L';                           // declaration token
const string declkey = "let";                   // declaration keyword


// Declare classes for Calculator
// Tokens
class Token{                                                    // a very simple user-defined type
public:
    char kind;                                                  // what kind of token
    double value;                                               // for numbers; a value
    string name;
    Token() : kind{0} {}                                        // default constructor
    Token(char ch) : kind{ch} {}                                // initialize kind with ch
    Token(char ch, double val) : kind{ch}, value{val} {}        // initialize kind and value
    Token(char ch, string n) : kind{ch}, name{n} {}             // initialize kind and name
};

class Token_stream {
public:
    Token get();                                // get a Token (get() is defined elsewhere)
    void putback(Token t);                      // put a Token back
    void ignore(char c);                        // discard characters up to and including a c
private:
    bool full{false};                           // is there a Token in the buffer?
    Token buffer{0};                            // here is where we keep a Token put back using putback()
};

// The ignore function in Token_stream to clean up after errors are caught
void Token_stream::ignore(char c)
{
    // first look in buffer
    if (full && c == buffer.kind){
        full = false;
        return;
    }
    full = false;

    // now search input:
    char ch = 0;
    while (std::cin >> ch)
        if (ch == c) return;
}

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;                                 // copy t to buffer
    full = true;                                // buffer is now full
}

Token Token_stream::get()
{
    if (full){                                  // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    std::cin >> ch;                             // ntoe that >> skips whitespace (space, newline, tab, etc.)
    
    switch (ch){
    case quit:
    case print:
    case '=':
    case '%':                                   // for modulo
    case '(': 
    case ')': 
    case '{': 
    case '}': 
    case '+': 
    case '-': 
    case '!': 
    case '*': 
    case '/':
        return Token(ch);                       // let the character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        {
            std::cin.putback(ch);               // put digit back into the input stream
            double val;
            std::cin >> val;                    // read a floating-point number
            return Token(number, val);          // let '8' represent "a number"            
        }
    default:
        if (isalpha(ch)){
            string s;
            s += ch;
            while (std::cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch;
            std::cin.putback(ch);
            if (s == declkey) return Token{let};    // declaration keyword
            return Token{name,s};
        }
        error("Bad token");
        return Token('?');                      // Never reached but satisfies compiler
    }
}

Token_stream ts;                                // provides functionality with get() and putback()

// Variable Classes
class Variable {
public:
    string name;
    double value;
};

// Vector of Variables (for storing such variables)
vector<Variable> var_table;


// Function declarations
double expression();
double term();
double factorial();
double primary();
void calculate ();
void clean_up_mess();
double get_value (string s);
void set_value(string s, double d);
double statement();
double declaration();
bool is_declared(string var);
double define_name(string var, double val);

// Main Body
int main()
try{
    // predefine names
    define_name("pi", 3.1415926535);
    define_name("e", 2.7182818284);

    // Welcome message
    std::cout   << "Welcome to our simple calculator. Please enter expressions using floating-point numbers.\n"
                << "You can use the following operators (+ - * /).\n"
                << "Please use ! for factorial cases with a non-negative integer.\n"
                << "Enter ';' to immediately print out the answer and 'q' to exit.\n";

    calculate();

    keep_window_open();
    return 0;
}

catch (exception& e){
    std::cerr << "error: " << e.what() << '\n';
    keep_window_open("~~");
    return 1;
}
catch(...){
    std::cerr << "exception!\n";
    keep_window_open("~~");
    return 2;
}

// Ancilliary Functions
void calculate ()                               // expression evaluation loop
{
    while (std::cin)
    try {
        std::cout << prompt;
        Token t = ts.get();
        while (t.kind == print) t = ts.get();   // first discard all "prints"
        if (t.kind == quit) return;             // quit
        ts.putback(t);
        std::cout << result << statement() << '\n';
    }
    catch (exception& e){
        std::cerr << e.what() << '\n';          // write an error message
        clean_up_mess();
    }
}

double statement()
{
    Token t = ts.get();
    switch(t.kind){
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();

    }
}

// Declare a variable called "name" with the initial value "expression"
double declaration()
{
    Token t = ts.get();
    if (t.kind != name) error("name expected in declaration");
    string var_name = t.name;

    Token t2 = ts.get();
    if (t2.kind != '=') error("= missing in declaration of ", var_name);

    double d = expression();
    define_name(var_name, d);
    return d;
}

void clean_up_mess()
{
    ts.ignore(print);    
}

double expression()
{
    double left = term();                       // read and evaluate a Term
    Token t = ts.get();                         // get the next Token from the Token stream
    while (true){
        switch(t.kind){
        case '+':
            left += term();                     // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();                     // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);                      // put t back into the token stream
            return left;                        // finally: no more + or -; return the answer
        }
    }
}

double term()
{
    // double left = primary();
    double left = factorial();
    Token t = ts.get();                         // get the next Token from the Token stream
    while (true){
        switch (t.kind){
        case '*':
            // left *= primary();
            left *= factorial();
            t = ts.get();
            break;
        case '/':
        {
            double d = factorial();
            if (d == 0) error("divide by zero");
            // left /= d;
            left /= d;
            t = ts.get();
            break;
        }
        case '%':
        {
            double d = primary();
            if (d == 0) error("%:divide by zero");
            left = fmod(left,d);
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);                      // put t back into the Token Stream
            return left;
        }
    }
}

double factorial()
{
    double left = primary();
    // By this point, left would be the value that we need to factorial, as it would have been called up recursively
    // Check for the factorial
    Token t = ts.get();
    if (t.kind == '!'){
        // error checking 
        if (left < 0) error("Factorial of negative number.");
        if (left != floor(left)) error("Factorial requires integer.");
        if (left>20) error("Factorial too large (>20). Overflow.");

        //
        double result = 1;              // accumulator starts at 1
        for (int i = int(left); i > 0; --i)
            result *= i;
        return result;
    } else {
        ts.putback(t);
        return left;
    }
}

double primary()
{
    Token t = ts.get();
    switch (t.kind){
    case '(':                                   // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return d;
    }
    case '{':                                   // handle '{' expression '}
    {
        double d = expression();
        t = ts.get();
        if (t.kind != '}') error("'}' expected");
        return d;
    }
    case number:                                // we use '8' to represent a number
        return t.value;                         // return the number's value
    case name:
        return get_value(t.name);
    case '-':
        return - primary();
    case '+':
        return primary();
    default:
        error("primary expected");
        return 0;                               // Never reached but satisfies compiler
    }
}

// Return the value of the Variable named s
double get_value (string s)
{
    for (const Variable& v : var_table){
        if (v.name == s) return v.value;
    }
    error("get: undefined variable ", s);
    return 0.0;
}

// Set the Variable named s to d
void set_value(string s, double d)
{
    for (Variable& v : var_table){
        if (v.name == s){
            v.value = d;
            return;
        }
    }
    error("set: undefined variable ", s);
}

// Is var already in var_table?
bool is_declared(string var)
{
    for (const Variable& v: var_table)
        if (v.name == var) return true;
    return false;
}

// Add {var, val} to var_table
double define_name(string var, double val)
{
    if (is_declared(var)) error(var, "declared twice");
    var_table.push_back(Variable{var,val});
    return val;
}