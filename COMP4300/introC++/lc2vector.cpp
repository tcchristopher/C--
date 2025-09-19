#include <iostream>
#include <vector>


int main()
{
    // std::vector<int> vec;
    // vec.push_back(42);
    // vec.push_back(10);

    //std::cout << vec[0] << "\n";
    //std::cout << vec[1] << "\n";
    //std::cout << vec[2] << "\n";    //  garbage values

    // for (size_t i = 0; i < vec.size(); i++)     // interestingly, the compiler does not throw a warning for the signed vs unsigned (int i vs vec.size)
    //                                             // so use size_t as a safe option
    // {
    //     std::cout << vec[i] << std::endl;   
    // }

    std::vector<float> vec;
    vec.push_back(42.2f);
    vec.push_back(10.1f);
    vec.push_back(11.3f);


    for (int a : vec)   // for everything in the vector, assign it the name of "a" and then do something {}
    {
        std::cout << a << std::endl;

    }

    // auto keyword

    //float a = vec[1];     // or
    //auto a = vec[1];     

    for (auto a : vec)              //  looks like new C++ actually corrects the auto typed thing even further than in the lecture video
    {
        std::cout << a << std::endl;
    }
    
    return 0;
}