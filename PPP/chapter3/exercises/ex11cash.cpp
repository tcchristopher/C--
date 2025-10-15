// A simple program that collates the cash coins that a user has in dollars and cents
#include <iostream>

int main()
{
    // Prompt the user for the amounts of coins they have
    std::cout << "Please enter the number of pennies (1-cent coins) you have: \n";
    int pennies = 0;
    std::cin >> pennies;
    std::cout << "Please enter the number of nickels (5-cent coins) you have: \n";
    int nickels = 0;
    std::cin >> nickels;
    std::cout << "Please enter the number of dimes (10-cent coins) you have: \n";
    int dimes = 0;
    std::cin >> dimes;
    std::cout << "Please enter the number of quarters (25-cent coins) you have: \n";
    int quarters = 0;
    std::cin >> quarters;
    std::cout << "Please enter the number of half-dollars (50-cent coins) you have: \n";
    int half_dollar = 0;
    std::cin >> half_dollar;
    std::cout << "Please enter the number of one-dollars (100-cent coins) you have: \n";
    int dollar = 0;
    std::cin >> dollar;

    // Collate the sum of their coins

    double cash_balance = ((pennies * 1) + (nickels * 5) + (dimes * 10) + (quarters * 25) + (half_dollar * 50) + (dollar * 100))/100.0;

    // Output their tally (with grammatical corrections)
    if (pennies > 0){                                               // non-zero tally only
        if (pennies == 1)
            std::cout << "You have 1 penny.\n";
        else
            std::cout << "You have " << pennies << " pennies.\n";
    }

    if (nickels > 0){
        if (nickels == 1)
            std::cout << "You have 1 nickel.\n";
        else
            std::cout << "You have " << nickels << " nickels.\n";
    }

    if (dimes > 0){
        if (dimes == 1)
            std::cout << "You have 1 dime.\n";
        else
            std::cout << "You have " << dimes << " dimes.\n";
    }

    if (quarters > 0){
        if (quarters == 1)
            std::cout << "You have 1 quarter.\n";
        else
            std::cout << "You have " << quarters << " quarters.\n";
    }

    if (half_dollar > 0){
        if (half_dollar == 1)
            std::cout << "You have 1 half-dollar.\n";
        else
            std::cout << "You have " << half_dollar << " half-dollars.\n";
    }

    if (dollar > 0){
        if (dollar == 1)
            std::cout << "You have 1 dollar coin.\n";
        else
            std::cout << "You have " << dollar << " dollar coins.\n";
    }

    // Output their cash balance
    std::cout << "The value of all of your coins is $" << cash_balance << ".\n";

    return 0;
}