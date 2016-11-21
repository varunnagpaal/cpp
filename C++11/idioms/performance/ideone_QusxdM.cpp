// Malloc
#include <iostream>
#include <ctime>

using namespace std;

void functVal( size_t sz)
{
    char *array;
    array = new char[sz];
    while( sz-- )
    {
        array[sz] = '\0';
    }
    delete[] array;
}

int main() 
{
    timespec tS;
    tS.tv_sec = 0;
    tS.tv_nsec = 0;
    clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tS);
    
    cout<<"Start"<<endl;
    
    for( int i = 0; i< 2000000; i++ )
    {
        functVal( 1000 );
    }
    
    cout<<"End"<<endl;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tS);
    cout << "Time taken is: " << tS.tv_sec << " " << tS.tv_nsec << endl;

    
    return 0;
}