// Raw and Smart pointers in C++11
#include <iostream>
using namespace std;

int main() 
{
	char *str = "literal string";
	const char *newstr = "another literal string";
	const char anotherstr[] = "yet another string"; 
	
	std::cout<< "str: " << str << std::endl 
			 << "newstr: " << newstr << std::endl
			 << "anotherstr: " << anotherstr << std::endl;
			 
	std::cout<< "str: " << *str << std::endl 
			 << "newstr: " << *newstr << std::endl
			 << "anotherstr: " << *anotherstr << std::endl;			 
	
	std::cout<< "sizeof(str): " << sizeof(str) << std::endl 			// sizeof pointer
			 << "sizeof(newstr): " << sizeof(newstr) << std::endl		// sizeof pointer
			 << "sizeof(anotherstr): " << sizeof(anotherstr) << std::endl;	// sizeof array of characters
			 
	std::cout<< "siseof(*str): " << sizeof(*str) << std::endl 
			 << "sizeof(*newstr): " << sizeof(*newstr) << std::endl
			 << "sizeof(*anotherstr): " << sizeof(*anotherstr) << std::endl;
			 
	char p[] = "modify";
	p[1] = 'a';
	std::cout << "p: " << p << std::endl;
	
	// runtime error
	//str[1] = 'i';		
	//std::cout << "str: " << str << std::endl ;
	
	// compilation error
	newstr[1] = 'i';		
	std::cout << "newstr: " << newstr << std::endl ;	
	
	return 0;
}