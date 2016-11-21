#include <iostream>

using namespace std;

class A
{
    public: virtual void funct(){ cout<<"A ";}
};

class B: public A
{
    public: void funct(){ cout<<"B ";}
};

class C: public B
{
    public: void funct(){ cout<<"C ";}
};

class DA: public A
{
    public: void funct(){ cout<<"DA ";}
};

int main()
{
    A objA;
    B objB;
    C objC;
    
    A* ptrA = NULL;
    ptrA = &objA;
    ptrA->funct();          // Virtual function call
    ptrA = &objB;           
    ptrA->funct();          // Virtual function call
    ptrA = &objC;
    ptrA->funct();          // Virtual function call
    
    DA objDA;
    A newObjA = objDA;      // Upcasting derived class object to base-class object
    ptrA = &objDA;
    ptrA->funct();          // Virtual function call    
    newObjA.funct();        // Non-virtual function call
    return 0;
}