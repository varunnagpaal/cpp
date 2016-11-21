#include <iostream>

using namespace std;

struct UnAlignPOD
{
    bool flag1; // Offset: 0
    // pad[]	// Offset: 1
    short var1; // Offset: 2,3
    bool flag2; // Offset: 4
    //pad[3]	// Offset: 5,6,7
    int var2;	// Offset: 8,9,10,11
};

struct AlignPOD
{
    bool flag1;	// Offset: 0
    bool flag2;	// Offset: 1
    short var1; // Offset: 2,3   
    int var2;   // Offset: 4,5,6,7
};

struct FinalPad {
  char n[1]; // Offset: 0
  // pad[7]	 // Offset: 1-7
  double x;  // Offset: 8-15
};

struct FinalPadShort {
  short s; 		// Offset: 0,1
  char n[3];    // Offset: 2,3,4
  // pad[1]     // Offset: 5
};

int main()
{
	cout << "Sizeof bool: " << sizeof(bool) << endl;
	cout << "Sizeof short int: " << sizeof(short int) << endl;
	cout << "Sizeof int: " << sizeof(int) << endl;
	cout << "Sizeof long int: " << sizeof(long int) << endl;
	cout << "Sizeof float: " << sizeof(float) << endl;
	cout << "Sizeof double: " << sizeof(double) << endl;
	cout << "Sizeof long double: " << sizeof(long double) << endl;
    cout << "Sizeof UnAlignPOD: " << sizeof(UnAlignPOD) << endl;
    cout << "Sizeof AlignPOD: " << sizeof(AlignPOD) << endl;
    cout << "Sizeof FinalPad: " << sizeof(FinalPad) << endl;
    cout << "Sizeof FinalPadShort: " << sizeof(FinalPadShort) << endl;
    
    return 0;
}