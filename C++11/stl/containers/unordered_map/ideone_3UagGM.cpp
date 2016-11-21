#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() 
{
	std::unordered_map<std::string, double> unord_map;
	
	std::cout << "Key: varun, value: " << unord_map["varun"]<<std::endl;
	// your code goes here
	return 0;
}