#include <iostream>

void pp(int & i)
{
    std::cout << &i << " " << i << " " << sizeof(i) << std::endl;   // print fucntion with pass by reference
                                                                    // for temporarily allocated primitives
}

class IntArray
{
    size_t m_size;
    int *m_arr;
    

public:

    IntArray(size_t size)
        : m_size(size)
        , m_arr (new int[size])             // zero'd
    {
        std::cout << "Array Constructor" << std::endl;
    }

    ~IntArray()
    {
        delete [] m_arr;
        std::cout << "Array Destructor" << std::endl;
    }

    int get(size_t index) const
    {
        return m_arr[index];
    }

    void set(size_t index, int val)
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

};


int main(int argc, char * argv[])
{
    IntArray myArray(10);

    myArray.set(4, 7);
    myArray.set(2, 134);

    myArray.print();
  

    return 0;
}