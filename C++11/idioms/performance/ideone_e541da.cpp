#include <ctime>
#include <iostream>

using namespace std;

namespace {
    class empty { }; // even empty classes take up 1 byte of space, minimum
}

int main()
{
    timespec tS;
    tS.tv_sec = 0;
    tS.tv_nsec = 0;
    clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tS);
    
    for (int i = 0; i < 50000000; ++i)
    {
        empty e;
    }
    
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tS);
    cout << "Time taken for stack allocation is: " << tS.tv_sec << " " << tS.tv_nsec << endl;
    
    clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tS);
    for (int i = 0; i < 50000000; ++i) 
    {
        empty* e = new empty;
        delete e;
    }
    
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tS);
    cout << "Time taken for heap allocation is: " << tS.tv_sec << " " << tS.tv_nsec << endl;
    
}