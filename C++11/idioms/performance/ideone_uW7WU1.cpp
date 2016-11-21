#include <iostream>

using namespace std;

// Size should be 12
struct UnAlignPOD
{
    bool flag1;
    short var1;
    bool flag2;
    int var2;
};

// Size should be 8
struct AlignPOD
{
    bool flag1;
    bool flag2;
    short var1;    
    int var2;
};


struct FinalPad {
  char n[1];
  double x;
  
};

// Size should be 5
struct FinalPadShort {
  short s;
  char n[3];                                                                                
};

int main()
{
    cout << "Sizeof object: " << sizeof(UnAlignPOD) << endl;
    cout << "Sizeof object: " << sizeof(AlignPOD) << endl;
    cout << "Sizeof object: " << sizeof(FinalPad) << endl;
    cout << "Sizeof double: " << sizeof(double) << endl;
    cout << "Sizeof object: " << sizeof(FinalPadShort) << endl;
    
    return 0;
}