#include <iostream>

void pp(int & i)
{
    std::cout << &i << " " << i << " " << sizeof(i) << std::endl;   // print fucntion with pass by reference
                                                                    // for temporarily allocated primitives
}

// GENERICS with Template

template <typename T>
// or template <class T>
class DynamicArray
{
    size_t m_size;
    T *m_arr;
    

public:

    DynamicArray(size_t size)
        : m_size(size)
        , m_arr (new T[size])             // zero'd
    {
        std::cout << "Array Constructor" << std::endl;
    }

    ~DynamicArray()
    {
        delete [] m_arr;
        std::cout << "Array Destructor" << std::endl;
    }

    T get(size_t index) const
    {
        return m_arr[index];
    }

    void set(size_t index, T val)
    {
        m_arr[index] = val;
    }

    void print() const
    {
        for (size_t i=0; i<m_size; ++i)
        {
            std::cout << i << " " << m_arr[i] << std::endl;
        }
    }

    // Operator Overloading
    // We can create a number of different operators in this class for any use

    T & operator [](size_t index)           // Call the square bracket operator via index, referencing it with &
    {
        return m_arr[index];     
    }

    // a second new T & operator would be needed to allow manipulation of the const Array (see line 83)
    // T & operator [](size_t index)
    //{
    //  return m_arr[index];
    //}

};


int main(int argc, char * argv[])
{
    DynamicArray<float> myArray(10);        // float or other variable defined here 

    // We want to be able to set the array in the C/C++ way
    // now with operator overload defined for [] operator:

    myArray[3] = 3.1459;                    // so now [3] becomes a reference for the & operator in the operator overload
    myArray[2] = 2.78;
    myArray[5] = 20;                        

    // myArray.set(4, 7.14);                // Now that we have the operator overload, we don't need to use set()
    // myArray.set(2, 134.420);

    // if I wanted to do a const DynamicArray<float> myArray(10) at 71,
    // I would need to add const at the end of the function T & operator [](size_t index) for const correctness
    // const in the beginning would let you see the data in a const way but not manipulate it (see line 60 for the solution)

    myArray.print();
  

    return 0;
}