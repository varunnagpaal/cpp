#include <iostream>
using namespace std;

int main() {
	// your code goes here
	int i=10;
	int *ptri = &i;
	int &refp = *ptri;
	int &refi = i;
	
	int *nollptr = nullptr;
	int &refnoll = *nollptr;
	
	
	std::cout<< "&i =" << &i <<std::endl;
	std::cout<< "ptri = " << ptri <<std::endl;
	std::cout << "&refp = " << &refp <<std::endl;
    std::cout << "&refi = " << &refi <<std::endl;
    
    std::cout<< "nollptr =" << nollptr <<std::endl;
    std::cout << "&refnoll = " << &refnoll <<std::endl;
	return 0;
}