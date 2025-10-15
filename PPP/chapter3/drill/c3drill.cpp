// A program to write a simple form letter based on user input
#include <iostream>
#include "std_lib_facilities.h"

int main()
{
    // Get the User's name
    std::cout << "What is your name? (followed by 'enter'): \n";
    std::string user_name;
    std::cin >> user_name;

    // Get the recipient's details from the User
    std::cout << "Enter the name of the person you want to write to and their age in years (followed by 'enter'):\n";
    std::string first_name;
    int age = 0;
    std::cin >> first_name >> age;

    //  Get the recipient's friend's details from the User
    std::cout   << "Enter the name of the second person you want to mention "
                << "in the letter and their sex (m or f), finally followed by 'enter': \n";
    std::string friend_name;
    char friend_sex = 0;
    std::cin >> friend_name >> friend_sex;
    while (friend_sex != 'm' && friend_sex != 'f'){
        std::cout << "Please enter the second person's sex again, either 'm' or 'f' only: \n";
        std::cin >> friend_sex;
    }
    
    // Letter reply begins here
    std::cout << "\nDear " << first_name << ",\n";
    std::cout << "  How are you?\n";
    std::cout << "I'm fine. I miss you.\n";
    std::cout << "It's been while since we've seen each other in person "
                << "and I can't forget what happened the last time.\n";
    std::cout << "So, I was hoping that we could see each other again.\n";

    // Check friend's gender and reply appropriately
    if (friend_sex == 'm')
        std::cout << "If you see " << friend_name << ", please ask him to call me.\n";
    else if (friend_sex == 'f')
        std::cout << "If you see " << friend_name << ", please ask her to call me.\n";
    
    // Respond to the recipient's age appropriately
    if (age <= 0 || age >= 110)
        simple_error("You're kidding!");
    else
        std::cout << "I hear you just had a birthday and you are " << age << " years old.\n";
        if (age <= 12)
            std::cout << "Next year, you will be " << age + 1 << ".\n";
        else if (age == 17)
            std::cout << "Next year, you will be able to vote!\n";
        else if (age >= 70)
            std::cout << "I hope you are enjoying retirement!\n";
    
    // End the letter
    std::cout << "Yours sincerely, \n\n\n" << user_name << '\n';
    return 0;
}