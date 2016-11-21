// Effective Modern C++
// Item 9: Alias declarations
#include <iostream>
#include <vector>

// Old style templatized typedef declaration
template<typename T>
struct TypeDefVecVec
{
	typedef std::vector<std::vector<T>> type;
};

// New style templatized alias declaration
template<typename T>
using AliasVecVec = std::vector<std::vector<T>>;

// Old style templatized function pointer using typedef
template<typename T>
struct FPold
{
	typedef void (*type)(T*, T);
};

// New style templatized function pointer using alias
template<typename T>
using FP = void (*)(T*, T);

template<typename T>
class Sample
{
	private:
		FP<T> newfp;					// doesnt require qualifer "typename"
		typename FPold<T>::type oldfp;	// does require qualifer "typename"
		
	public:
};
void Hello( int* list, int size)
{
}

int main()
{
	// your code goes here
	FP<int>			 			myfunc 		= Hello;
	FPold<int>::type 			myoldfunc 	= Hello;
	TypeDefVecVec<float>::type 	myvecvec1;
	AliasVecVec<float> 			myvecvec2;
	return 0;
}