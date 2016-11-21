#include <iostream>
#include <sstream>
using namespace std;

int main() 
{
	const auto size = 10;
	std::stringstream *arrayStrStrm = new std::stringstream[size];
	
	for( auto i = 0; i< size; ++i )
	{
		arrayStrStrm[i] << i << std::endl;
	}
	
	for( auto i = 0; i< size; ++i )
	{
		std::cout << arrayStrStrm[i].str();
		arrayStrStrm[i].empty();
	}	
	delete [] arrayStrStrm;
	return 0;
}