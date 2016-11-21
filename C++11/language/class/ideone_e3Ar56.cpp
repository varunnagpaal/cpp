#include <iostream>
 
using namespace std;
 
class A
{
    private : int i;
    public: void funct(){i++; cout<<"i:"<<i<<endl;}
            void anFunct(){ cout<<"A "<<endl; }
};

int main()
{
    A* ptrA = NULL;
    ptrA->anFunct();
    ptrA->funct();
    return 0;
}