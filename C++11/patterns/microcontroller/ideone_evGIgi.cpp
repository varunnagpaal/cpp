// Bit-fields

#include <iostream>
#include <stdint.h>
using namespace std;

// C++ bit-filed
struct HEADER
{
	uint32_t source;
	uint32_t destination;
	uint32_t version: 4;
	uint32_t protocol: 4;
	uint32_t lenght: 12;
	uint32_t flags: 4;
	uint32_t : 6;	//unused
	bool valid: 1;
	bool global: 1;
};

// 5-bit set
// Likely to be packed in a single byte ..the smallest
// unit of alignment that compiler can handle
struct ONEBYTEALIGNED
{
	unsigned char c: 2;
	unsigned char d: 2;
	bool e: 1;
};


struct NONEBYTEALIGNED
{
	unsigned char c: 2;
	unsigned char d: 2;
	bool e: 1;
	
	unsigned char f: 4;
};

int main() {
	// your code goes here
	HEADER h;
	h.valid =10;
	
	std::cout << "Sizeof(HEADER):" <<sizeof(HEADER) << std::endl;
	std::cout << "Sizeof(ONEBYTEALIGNED):" <<sizeof(ONEBYTEALIGNED) << std::endl;
	std::cout << "Sizeof(NONEBYTEALIGNED):" <<sizeof(NONEBYTEALIGNED) << std::endl;
	
	return 0;
}