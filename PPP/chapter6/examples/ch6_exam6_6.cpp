// First version of the full Calculator
#include "std_lib_facilities.h"

class Token{                                    // a very simple user-defined type
public:
    char kind;                                  // what kind of token
    double value;                               // for numbers; a value
    Token(char k):kind{k}, value {0.0}{}            // construct from one value
    Token(char k, double v):kind{k}, value{v}{}     // construct from two values
};

Token get_token();                              // function to read a token from std::cin

double expression();
double term();
double primary();

int main()
try{
    while(std::cin)
        std::cout << "=" << expression() << '\n';
    keep_window_open();
}
catch (exception& e){
    std::cerr << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch(...){
    std::cerr << "exception \n";
    keep_window_open();
    return 2;
}

Token get_token()                               // read a token from std::cin
{
    char ch;
    std::cin >> ch;                             // note that >> skips whitespace (space, newline, tab, etc)

    switch (ch){
        // TODO case ';':                       // for "print"
        // TODO case 'q':                       // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/':
        return Token(ch);                       // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        std::cin.putback(ch);                   // put digit back into the input stream
        double val;
        std::cin >> val;                        // read a floating-point number
        return Token('8', val);                 // let '8' represent "a number"
    }
    default:
        error("Bad token");
    }
}

double expression()
{
    double left = term();                       // read and evaluate a Term
    Token t = get_token();                      // get the next token
    while (true){
        switch(t.kind){
        case '+':
            left += term();                     // evaluate Term and add
            t = get_token();
            break;
        case '-':
            left -= term();                     // evaluate Term and subtract
            t = get_token();
            break;
        default:
            return left;                        // finally: no more + or -; return the answer
        }
    }
}

double term()
{
    double left = primary();
    Token t = get_token();
    while (true){
        switch (t.kind){
        case '*':
            left *= primary();
            t = get_token();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = get_token();
            break;
        }
        default:
            return left;
        }
    }
}

double primary()
{
    Token t = get_token();
    switch (t.kind){
    case '(':                                   // handle '(' expression ')'
    {
        double d = expression();
        t = get_token();
        if (t.kind != ')') error("')' expected");
        return d;
    }
    case '8':                                   // we use '8' to represent a number
        return t.value;                         // return the number's value
    default:
        error("primary expected");
    }
}