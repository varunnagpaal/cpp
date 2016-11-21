#include <iostream>
#include  <iomanip>
using namespace std;

int main() 
{
	std::cout << std::setw(24) << std::left << "Hello" << std::setw(24) << "World" <<std::endl;
	std::cout << std::setw(24) << "" << std::setw(24) << "Hello" << std::setw(24) << "World" <<std::endl;
	
	return 0;
}