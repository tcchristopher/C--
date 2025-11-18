
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

// updated to be the primary exercise file

#include "std_lib_facilities.h"

// Structures and Classes for the program, using Token, Token_stream and Symbol_table class
struct Token {
	char kind;													// what kind of token
	double value;												// for numbers to be calculated - a value
	string name;
	Token(char ch) :kind(ch), value(0) { }						// initialize kind with ch only
	Token(char ch, double val) :kind(ch), value(val) { }		// initialize kind and value
	Token(char ch, string n) : kind{ch}, name{n} { }			// initialize kind and name
};

class Token_stream {											// moved the initializers for full and buffer to their respective declarants in private
public:
	Token get();												// get a Token (get() is defined elsewhere)
	void unget(Token t);										// unget() is defined elsewhere
	void ignore(char c);										// discard characters up to and including a c
private:														// moved into private
	bool full{false};											// is there a Token in buffer?
	Token buffer{0};											// a token that is kept here for put back through unget()
};

// variable classes
struct Variable {
	string name;
	double value;
	bool is_const;											// for adding in user defined constants
	Variable(string n, double v, bool c = false) :name(n), value(v), is_const(c) { }
};

class Symbol_table {
private:
	vector<Variable> var_table;
public:
	double get(string s);										// former get_value()
	void set(string s, double d);								// former set_value()
	bool is_declared(string s);									// same name
	void declare(string n, double v, bool is_const = false);	// new
};

// The unget() member function puts its argument back into the Token_stream's buffer:
void Token_stream::unget(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;                                 // copy t to buffer
    full = true;                                // buffer is now full
}

// Constant declarations for the program
const char let = '#';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char sqroot = 'S';						// for a square root function
const char power = 'P';							// for a power exponent function
const char constant = 'C';						// for user-added constants				

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }					// if there already is a token, remove token from buffer
	char ch;

	//cin >> ch; OLD
	// NEW: Need to handle whitespace seperately to validate the return key ("\n")

	if (!cin.get(ch)) return Token(quit);						// End of File

	// handle whitespace
	if (isspace(ch)){
		if (ch == '\n') return Token(print);					// newline
		if (!cin.get(ch)) return Token(quit);					// End of File
	}

	// Continue the switch
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case ',':
	case '=':
	case '#':
		return Token(ch);										// let the character represent itself in this case
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		{	
			cin.unget();										// put the digit back into the input stream
			double val;
			cin >> val;											// read a floating-point number
			return Token(number, val);							// let the constant '8' represent the kind (number)
		}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.unget();										// unget() is superior over putback() because it handles most recently accessed memory in iostream
			//if (s == "let") return Token(let);
			if (s == "exit") return Token(quit);
			if (s == "sqrt") return Token(sqroot);				// handles the reading of the term sqrt in the token stream as 'S'
			if (s == "pow") return Token(power);				// handles the reading of the term pow in the token stream
			if (s == "const") return Token(constant);			// handles the reading of user-defined constants
			return Token(name, s);
		}
		error("Bad token");
		return Token('?');                      // Never reached but satisfies compiler
	}
}

// the ignore function in Token_stream to clean up after errors are caught
void Token_stream::ignore(char c)
{
	// first look in buffer
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	// now search input
	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

// Symbol table of symbols (for storing names)
Symbol_table symbols;

// return the value of a string variable for vector names
double Symbol_table::get(string s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;
	error("get: undefined name ", s);
	return 0.0;
}

// set the variable named s to value of d
void Symbol_table::set(string s, double d)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) {
			if (var_table[i].is_const){
				error("can't change constant ", s);
			}
			var_table[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

// Is var already in the table?
bool Symbol_table::is_declared(string s)
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return true;
	return false;
}

// Symbol_table declaration
void Symbol_table::declare(string n, double v, bool is_const)
{
	if(is_declared(n)) error(n, " declared twice");
	var_table.push_back(Variable(n, v, is_const));
}

Token_stream ts;											// provides the code with the functionality of get() and unget()

double expression();										// so that it can be used in primary()

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':
		return - primary();
	case '+':
		return primary();
	case sqroot:								// square root is a unary operator (primary) acting on one expression i.e. sqrt(expression)
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected after sqrt");
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		if (d < 0) error("sqrt of a negative number");
		return sqrt(d);							// actual calculation here
	}
	case power:
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected after pow");
		
		double x = expression();				// first argument (base)

		t = ts.get();
		if (t.kind != ',') error("',' expected in pow");

		double i = expression();				// second argument (exponent)

		t = ts.get();
		if (t.kind != ')') error("')' expected after pow");

		// Validate that i is an integer
		if (i != int(i)) error("pow: second argument must be an integer");

		// Make double sure that integer is usd for exponent
		int exponent = int(i);
		double result = 1;

		// Check for negative exponent
		if (exponent < 0) {
			error("pow: negative exponent not supported");
		}

		for (int n = 0; n < exponent; ++n){
			result *= x;
		}

		return result;
	}
	case number:
		return t.value;
	case name:
		return symbols.get(t.name);
	default:
		error("primary expected");
		return 0;                               // Never reached but satisfies compiler
	}
}

double term()
{
	double left = primary();
	while (true) {
		Token t = ts.get();						// Should be fine as the while (true) loop is good until broken
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		// add in Modulo functionality
        case '%':
        {
            double d = primary();
            if (d == 0) error("%:divide by zero");
            left = fmod(left,d);
            break;
        }
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	if (symbols.is_declared(var_name)) error(var_name, " declared twice");

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression();
	symbols.declare(var_name, d);											// for regular variables
	return d;
}

// User-defined constants
double const_declaration()
{
    Token t = ts.get();
    if (t.kind != name) error("name expected in constant declaration");
    string var_name = t.name;

    if (symbols.is_declared(var_name)) error(var_name + " declared twice");

    Token t2 = ts.get();
    if (t2.kind != '=') error("= missing in declaration of " + var_name);

    double d = expression();
    symbols.declare(var_name, d, true);  									// for constants
    return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	case constant:
		return const_declaration();
	default:
	// Check if this is an assignment (name = expression)
	if (t.kind == name){
		Token t2 = ts.get();
		if (t2.kind == '='){							// then it is an assignment
			string var_name = t.name;
			double d = expression();
			symbols.set(var_name, d);						// this will check is_const
			return d;
		}
		// not an assignment so put the token back and evaluate as an expression
		ts.unget(t2);
	}
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()									// expression evaluation loop
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();		// first disard all "prints"
		if (t.kind == quit) return;					// quit
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;					// write an error message
		clean_up_mess();
	}
}

int main()

try {
	// Define predefined names
	symbols.declare("k", 1000);
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}
