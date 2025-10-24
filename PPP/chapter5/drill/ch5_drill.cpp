// This is the Drill exervise for Chapter 5 Errors
#include "std_lib_facilities.h"

int main()
try{
    //std::cout << "Success!\n";                    STEP 1
    //std::cout << "Success!\n";                    STEP 2
    //std::cout << "Success!" << "!\n";             STEP 3
    //std::cout << "Success!" << '\n';              STEP 4
    //int res = 7; vector<int> v(10); v[5] = res; std::cout << "Success!\n";    STEP 5
    //vector<int> v(10); v[5] = 7; if (v[5]==7) std::cout << "Success!\n";      STEP 6
    //if(true) std::cout << "Success!\n"; else std::cout << "Fail!\n";          STEP 7
    //bool c = false; if (!c) std::cout << "Success!\n"; else std::cout << "Fail!\n"; STEP 8
    //string s = "ape"; bool c = false; if (!c) std::cout << "Success!\n";      STEP 9
    //string s = "ape"; if (s != "fool") std::cout << "Success!\n";             STEP 10
    //string s = "ape"; if (s!="fool") std::cout << "Success!\n";               STEP 11
    //string s = "ape"; if (s+"fool"=="apefool") std::cout << "Success!\n";     STEP 12
    //vector<char> v(5); for (int i=0; i<v.size(); ++i) v[i] = 0; std::cout << "Success!\n";    STEP 13
    //vector<char> v(5); for (int i=0; i<v.size(); ++i) v[i] = 0; std::cout << "Success!\n";    STEP 14
    //string s = "Success!\n"; for (int i=0;i<s.size(); ++i) std::cout << s[i]; STEP 15
    //if (true) std::cout << "Success!\n"; else std::cout << "Fail!\n";         STEP 16
    //int x = 2000; int c = x; if (c==2000) std::cout << "Success!\n";          STEP 17
    //string s = "Success!\n"; for (int i=0; i<s.size(); ++i) std::cout << s[i];    STEP 18
    //vector<int>v(5); for (int i=0; i<v.size(); ++i) v[i] = 0; std::cout << "Success!\n";      STEP 19
    //int i=0; int j=9; while(i<10) ++i; if (j<i) std::cout << "Success!\n";    STEP 20
    //int x = 2; double d = (5.0/x)+2; if (d==2*x+0.5) std::cout << "Success!\n";   STEP 21
    //string s = "Success!\n"; for(int i=0; i<s.size(); ++i) std::cout << s[i]; STEP 22
    //int i=0; int j=0; while (j<10) ++j; if (j>i) std::cout << "Success!\n";   STEP 23
    //int x=4; double d = 5.0/(x-2); if (d==x/2+0.5) std::cout << "Success!\n"; STEP 24
    std::cout << "Success!\n";
    keep_window_open();
    return 0;
}
catch (exception& e){
    std::cerr << "error: " << e.what() << '\n';
    keep_window_open();
    return 1;
}
catch (...){
    std::cerr << "Oops: unknown exception!\n";
    keep_window_open();
    return 2;
}