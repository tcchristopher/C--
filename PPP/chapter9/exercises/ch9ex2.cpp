#include "std_lib_facilities.h"
//test
class Name_pairs {

    vector<string> names;
    vector<double> ages;

public:

    void read_names();
    void read_ages();
    void print();
    void sort();
};

void Name_pairs::read_names()
{
    string name;
    while (std::cin >> name){
        if (name != "exit"){
            names.push_back(name);
        } else {
            break;
        }
    }
}

void Name_pairs::read_ages()
{
    double age;
    for (int i = 0; i < names.size(); i++){
        std::cout << "Please enter the age for " << names[i] << ": ";
        std::cin >> age;
        if (std::cin){
            ages.push_back(age);
        } else {
            std::cerr << "Incorrect input. Please try again.";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            --i;
        }
    }
}


void Name_pairs::print()
{
    for (int i = 0; i < names.size(); ++i){
        std::cout << names[i] << ", " << ages[i] << '\n';
    }

}

void Name_pairs::sort()
{
    vector<string> original_names = names;
    std::sort(names.begin(), names.end());

    vector<double> new_ages (ages.size());

    for (int i = 0; i < names.size(); ++i){
        for (int k = 0; k < original_names.size(); ++k){
            if (original_names[k] == names[i]){
                new_ages[i] = ages[k];
                break;
            }
        }
    }

    ages = new_ages;
}

int main()
{
    Name_pairs contacts;

    std::cout << "Welcome to the program!\n";
    std::cout << "Please input the collection of names, spaced by a return line per name.\n";

    contacts.read_names();

    std::cout << "Please input the ages of each person as follows: \n";

    contacts.read_ages();

    contacts.print();

    contacts.sort();

    std::cout << "Sorted order: \n";

    contacts.print();
    

}