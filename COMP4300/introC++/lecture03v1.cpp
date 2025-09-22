#include <iostream>

void pp(int & i)
{
    std::cout << &i << " " << i << " " << sizeof(i) << std::endl;   // print fucntion with pass by reference
                                                                    // for temporarily allocated primitives

}

int main(int argc, char * argv[])
{
    // int a = 10;     // stack-allocated variables
    // int b = 25;

    // pp(a);
    // pp(b);

    int arr[10]= {};                // no values populated right now but = {} adds default values
    // int *harr = new int[10];        // heap array

    for (size_t i=0; i < 10; i++)
    {
        pp(arr[i]);                 // will populate with garbage values unless = {}
    }

    // for (size_t i=0; i < 10; i++)
    // {
    //     pp(harr[i]);                 // this didn't populate with garbage data because of new
    // }


    return 0;
}