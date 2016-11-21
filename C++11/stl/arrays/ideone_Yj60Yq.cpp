// Variable length arrays C99
#include <iostream>
#include <ctime>

using namespace std;

void functVal( size_t sz)
{
    char array[sz];
    while( sz-- )
    {
        array[sz] = '\0';
    }
}

int main() 
{
    timespec tS;
    tS.tv_sec = 0;
    tS.tv_nsec = 0;
    clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tS);
    
    cout<<"Start"<<endl;
    
    for( int i = 0; i< 2000000000; i++ )
    {
        functVal( 10000000000 );
    }
    
    cout<<"End"<<endl;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tS);
    cout << "Time taken is: " << tS.tv_sec << " " << tS.tv_nsec << endl;

    
    return 0;
}