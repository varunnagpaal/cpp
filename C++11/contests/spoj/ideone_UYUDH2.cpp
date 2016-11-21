#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
using namespace std;

int main() {
	
	string str1, str2;
	uint32_t num1, num2;

	// skip first line
	while( std::cin >> str1 )
	{
		break;
	}
	
	// Read next lines
	while( std::cin >> str1 >> str2 )
	{
		// Reverse
		std::reverse( str1.begin(), str1.end() );
		std::reverse( str2.begin(), str2.end() );
		
		// sum
		auto result = std::stoul( str1) + std::stoul(str2);
		
		// to string
		auto resultstr = std::to_string( result );
		
		// reverse
		std::reverse( resultstr.begin(), resultstr.end() );
		
		// to int
		// this is slow
		// auto finalres = std::stoul( resultstr );
		// alternatively remove leading zeros
		resultstr.erase(0, resultstr.find_first_not_of('0') );
		
		std::cout << resultstr  << std::endl;
	}
	return 0;
}