// Error Reporting
#include "std_lib_facilities.h"

char ask_user(std::string question);
int area(int length, int width);

int main ()
{

}

// ask user for a yes-or-no answer
// return 'b' to indicate a bad answer (i.e. not yes or no)
char ask_user(std::string question)
{
    std::cout << question << "? (yes or no)\n";
    std::string answer = " ";
    std::cin >> answer;
    if (answer == "y" || answer == "yes") return 'y';
    if (answer == "n" || answer == "no") return 'n';
    return 'b'; // b for "bad answer"
}

// calculate the area of a rectangle
// return -1 to indicate a bad argument
int area(int length, int width)
{
    if (length<-0 || width <=0) return -1;
    return length*width;

}