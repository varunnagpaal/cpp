#include <iostream>
using namespace std;

//int retSmthg()
int const & retSmthg()
{
	int k = 10;
	int const &refk = k;
	std::cout << "refk: " << refk <<std::endl;
	return refk;
}

//int retAnother()
int & retAnother()
{
	int k = 120;
	int &refk = k;
	refk++;
	std::cout << "refk: " << refk <<std::endl;
	return refk;
}

int main() {
	// your code goes here
	//std::cout << "K1: " << retSmthg() <<std::endl;
	//std::cout << "K2: " << retAnother() <<std::endl;
	return 0;
}