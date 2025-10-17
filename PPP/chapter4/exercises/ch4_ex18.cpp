// Solve the quadratic equation!
#include <iostream>
#include <cmath>

int main()
{
    // Initialise the variables to be solved and the answers
    double a = 0;
    double b = 0;
    double c = 0;
    double x1 = 0;
    double x2 = 0;

    // Let the user know about the inputs
    std::cout << "Please enter the following values as per the quadratic standard: ax^2 + bx + c = 0 :\n";
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    std::cout << "c = ";
    std::cin >> c;

    // Check if actually a quadratic
    if (a == 0){
        std::cout << "Error: 'a' cannot be 0 (not a quadratic equation) \n";
        return 1;
    }

    // Solve the discriminant and check for error
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0){
        std::cout << "No real solutions as discriminant (b^2-4ac) is negative and sqrt(-) is undefined.\n";
    }
    else if (discriminant == 0){
        double x = -b/(2*a);
        std::cout << "One solution: x = " << x << "\n";
    } // Solve for the quadratic solutions as per the forumla: x1 and x2 = (-b+-sqrt(b^2-4*a*c))/(2*a)
    else{
        x1 = (-b + sqrt(discriminant))/(2*a);
        x2 = (-b - sqrt(discriminant))/(2*a);
        
        // Output the results
        std::cout << "The two results of the quadratic are: " << x1 << " and " << x2 << ".\n";
    }
    return 0;
}