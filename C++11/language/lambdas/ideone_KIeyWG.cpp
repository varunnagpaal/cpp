// lambda examples
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>


int main() 
{
	std::vector<int> myvec = {2,4,1,22,14,23,14,-1,-6,90};
	
	auto sorter = []( int const & a, int const & b){ return a<b; };
	auto printer =[]( int a){ std::cout << a << ", ";};
	
	for_each( myvec.begin(), myvec.end(), printer );
	std::cout << std::endl;
	std::sort(myvec.begin(),myvec.end(), sorter);
	for_each( myvec.begin(), myvec.end(), printer );
	std::cout << std::endl;
	return 0;
}