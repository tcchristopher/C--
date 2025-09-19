#include <iostream>
#include <vector>
#include <fstream>

// Make a class

class Student
{// private
    std::string m_first = "First";
    std::string m_last  = "Last";
    int         m_id    = 0;
    float       m_avg   = 0;

public:
    //constructor
    Student() {}    //  if nothing happens

    Student(std::string first, std::string last, int id, float avg) //  initializer
        : m_first   (first)
        , m_last    (last)
        , m_id      (id)
        , m_avg     (avg)
    {
    }

    int getAvg() const      // const correctness as getAvg won't change the values
    {
        return m_avg;
    }

    int getID() const       // const correctness
    {
        return m_id;
    }

    std::string getFirst() const
    {
        return m_first;
    }

    std::string getLast() const
    {
        return m_last;
    }

    // void print() // in this form, the function could change the values of s3, which is const. Hence compile error
    // {
    //     std::cout << m_first << " " << m_last << " ";
    //     std::cout << m_id << " " << m_avg << std::endl;
    // }

    void print() const  // now the function itself is const, meaning it can't change the values of the const class
    {
        // m_first = "Joe"; //  this is the tester for the const change
        std::cout << m_first << " " << m_last << " ";
        std::cout << m_id << " " << m_avg << std::endl;
    }
};

// void doMachineLearning(const Data& d)         //  canonical use of a const class, with big data structure Data, or a sprite,
//                                               //  passed through as a reference & for safety (could be a pointer if wanted)
// {
//     d.getValue()
// }

class Course
{
    std::string m_name = "Course";
    std::vector<Student> m_students;

public:

    Course() {}

    Course(const std::string& name)    //  strings are big memory items. We should copy the reference & instead to save on data
        :   m_name(name)
    {
    }

    void addStudent(const Student& s)
    {
        m_students.push_back(s);
    }

    const std::vector<Student>& getStudents() const     //  C++ returns by value, and in this case, it would take on the type of Student,
                                                        //  so pass reference & instead. The last const means that getStudents function will
                                                        //  not change the class Student. The first const means that whatever we're
                                                        //  returning cannot be changed.
    {
        return m_students;
    }

    // File reading function to load student details
    void loadFromFile(const std::string& filename)
    {
        std::ifstream fin(filename);
        // std::string temp;

        // while (fin >> temp)     // fin send string tokens to temp until there are no more tokens >>
        // {
        //     std::cout << temp << std::endl;
        // }

        std::string first, last;
        int id;
        float avg;

        while (fin >> first)     // fin send string tokens to first until there are no more tokens >>
        {
            // fin >> last;
            // fin >> id;
            // fin >> avg;

            // or

            fin >> last >> id >> avg;

            addStudent(Student(first, last, id, avg));
        }

    }

    void print() const
    {
        for (const auto& s : m_students)
        {
            s.print();
        }
    }

};


int main()
{
    // Student s1;
    // Student s2("Thabiso", "Christopher", 1, 3.14);
    // Student s3("Jane", "Darling", 202200001, 99.9);

    // Course comp4300("COMP 4300");
    // comp4300.addStudent(s1);
    // comp4300.addStudent(s2);
    // comp4300.addStudent(s3);
    // comp4300.addStudent(Student("Billy", "Bob", 202200002, 50.0));

    // comp4300.print();
   
    Course c("COMP 4300");                  //  Creates the course
    c.loadFromFile("students.txt");         //  Load the data from the file
    c.print();                              //  Prints out the data (3 lines total for the main function)

    return 0;
}