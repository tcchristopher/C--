// Drill Exercise from Chapter 4 of Stroustrup's PPP
#include <iostream>
#include <cmath>

int main()
{
    // Integer version
    // int read_num1 = 0;
    // int read_num2 = 0;

    // Double version
    // double read_num1 = 0;
    // double read_num2 = 0;

    // Single variable read
    double input_num = 0;
    double smallest_num = 0;
    double largest_num = 0;

    // Length conversion
    std::string unit = " ";
    std::string meters = "m";

    // A while loop that terminates when for invalid input (non-numerical)
    // while(std::cin >> input_num >> unit){
        //std::cout << "DEBUG: Read " << input_num << " and '" << unit << "'\n";  // ADD THIS
        //std::cout << "\nYour two integers are : " << read_num1 << " and " << read_num2 << "\n\n";
        
        // // Which is the smaller and larger of the numbers
        // if (read_num1 > read_num2){
        //     std::cout << "The smaller value is: " << read_num2 << '\n';
        //     std::cout << "The larger value is: " << read_num1 << "\n\n";
        // }
        // else if (read_num1 == read_num2){
        //     std::cout << "The numbers are equal. \n\n";
        // }
        // else{
        //     std::cout << "The smaller value is: " << read_num1 << '\n';
        //     std::cout << "The larger value is: " << read_num2 << "\n\n";
        // }

        // // Are the numbers almost equal?
        // if (std::abs(read_num1 - read_num2) <= (1.0/100))
        //     std::cout << "The numbers are almost equal.\n";
    while(true){
        std::cout << "Ready for input...\n";  // ADD THIS
        if (!(std::cin >> input_num)) {
            std::cout << "Failed to read number\n";
            std::cout << "Stream state - fail: " << std::cin.fail() 
                    << " bad: " << std::cin.bad() 
                    << " eof: " << std::cin.eof() << "\n";
            
            // Try to see what character caused the failure
            std::cin.clear();
            char ch;
            if (std::cin >> ch) {
                std::cout << "Next char in stream: '" << ch << "'\n";
            }
            break;
        }

        // Convert any of the four accepted units to meters
        if (unit == "m"){
        }
        else if (unit == "cm"){
            input_num *= 0.01;
        }
        else if (unit == "in"){
            input_num *= 0.0254;
        }
        else if (unit == "ft"){
            input_num *= 0.3048;
        }
        else {
            std::cout << "Invalid unit: " << unit << "\n";
        continue;  // Skip this input
        }
        
        // Output the smallest and largest numbers thus far
        // Initialise the boundary numbers from zero
        if (smallest_num == 0 && largest_num == 0){
            smallest_num = input_num;
            largest_num = input_num;
        }

        // Check, store and output
        if (input_num < smallest_num){
            smallest_num = input_num;
            std::cout << "The smallest number so far (" << smallest_num << "m)\n";
        }
        else if (input_num > largest_num){
            largest_num = input_num;
            std::cout << "The largest number so far (" << largest_num << "m)\n";
        }
    }
}