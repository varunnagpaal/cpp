#include <iostream>
#include <vector>
#include <iterator> 
using namespace std;

int main() {
	std::vector<int> intvec = {8,9};
	
	for( auto i = intvec.size(); i>0; --i )
	{
		std::cout << intvec[i-1] << "[" << i-1 << "]," ;
	}
	
	std::cout << std::endl;
	
	for( auto it = intvec.rbegin(); it!= intvec.rend(); ++ it)
	{
		auto num = *it;
		std::cout << num << "[" << std::distance(it,intvec.rend()-1) << "]," ;
	}
	// your code goes here
	return 0;
}