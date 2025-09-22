#include <iostream>

void pp(int & i)
{
    std::cout << &i << " " << i << " " << sizeof(i) << std::endl;   // print fucntion with pass by reference
                                                                    // for temporarily allocated primitives

}

int main(int argc, char * argv[])
{
    int   a = 10;
    int   b = 25;
    int *pa = &a;
    int *pb = &b;

    // *pa = 17;        // changes through the reference of &a
    // *(&a) = 17;         // equivalent to above because pa is a reference

    *(pb-1) = 17;       //  modifies the data at an integer's distance (4 bytes) away from b, which is a.
                        //  Which doesn't happen here. This C++ version must correct this automatically.
    
    pp(a);
    pp(b);
    // pp(pa);     // can't be done as pp is expecting a variable/reference, not a pointer
    // pp(pb);     // can't be done as pp is expecting a variable/reference, not a pointer

   

    return 0;
}