#include <iostream>
using namespace std;

/* 
 Size of a structure depends upon
 - CPU Architecture 32-bit/64-bit
 - Order of layout of data members

 Alignment of a structure is equal to alignment of member with largest
 alignment requirement
 
 Size of a structure must be multiple of its alignment
 
 A data member is naturally aligned if its address is multiple of its size
 Padding is done in a structure to ensure each member is naturally aligned.
 Padding can only be done: 
 - between adjacent members  i.e. "Internal Padding" or "holes in Pahole"
 - after last data member i.e. "Trailing Padding" or "padding in pahole"
 Note: "leading padding" is not allowed by C standard
 
 Also, memory access granularity of processor determines how many
 accesses are needed to access a particular data. Example: On a 
 32-/64 bit machine, granularity is 4/8 bytes. So accessing a 
 double (8 byte aligned), would require 2 / 1 accesses on 32/64 bit machine
*/

struct X
{
	char a; 	// Offset:0
	// pad[3]   // Offset:1,2,3
	long int b; // Offset: 4,5,6,7
	char c;		// Offset: 8
	//pad[1]    // Offset: 9
	short int d;// Offset: 10,11
	long int e; // Offset: 12,13,14,15
	float f;    // Offset: 16,17,18,19
};

int main() {
	std::cout<<"Sizeof(short int): "<<sizeof(short int)<<std::endl;
	std::cout<<"Sizeof(int): "<<sizeof(int)<<std::endl;
	std::cout<<"Sizeof(long int): "<<sizeof(long int)<<std::endl;
	std::cout<<"Sizeof(float): "<<sizeof(float)<<std::endl;
	std::cout<<"Sizeof(double): "<<sizeof(double)<<std::endl;
	std::cout<<"Sizeof(X): "<<sizeof(X)<<std::endl;
	return 0;
}