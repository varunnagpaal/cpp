// keyword auto
// reduces code verbosity by infrencing types which are verbose and error prone to write
// Why we need auto ?
// 1. Dont repeat yourself (DRY)
// 2. High level of abstraction and coding to interfaces
// 3. Make future proof the code as types internals can change without changing client code that uses them  
// 4. Eases refactoring as for example change of class names and function return types
// 5. Simpler template code as auto can be used to specify intermediate types which depend upon actual type
// 6. Declaring variables of undocumented or unnamable types (example lambda expressions)
//
// type inferred for declarator
// Use auto as long as code doesn't require type conversion

#include <iostream>
#include <vector>

class someClass
{
public:

	// auto cannot be used for declaring member variables
	// auto _var;

	// auto cannnot be used for declaring function parameters
	// void Func(auto param1);

	// user specified default constructor
	someClass() 
	{

	}

	// cannot use auto with explicit copy constructors
	// user specified explicit copy constructor
	explicit someClass(someClass const & obj)
	{

	}
};

void globalFunc(int a, float b)
{

}

int main()
{
	// auto cannot be used to declare arrays
	// auto myarr[100];

	// auto for simple built-in types
	auto a = 5.0;
	auto b = 10.0;
	auto i = 1.0;
	auto *ptr = &a, &ref = b;
	//auto j = 10, str = "error"; // compile error since j and str have different types

	// auto for objects of containers
	std::vector<int> vec1;
	auto &refmyvec1 = vec1;				// reference to vector
	auto *ptrmyvec1 = &vec1;			// pointer to vector
	const auto &constrefmyvec1 = vec1;	// reference to constant vector
	const auto *ptrconstmyvec1 = &vec1;	// pointer to constant vector
	const auto * const constptrconstmyvec = &vec1;	// constant pointer to constant vector
	const auto & const constrefconstmyvec = vec1;	// constant reference to constant vector
	
	// When infrencing type for declared variable (variable on left side of =) 
	// from an intializer variable (variable on right side of =) which is const or volatile, 
	// the const and volatile specifiers are removed in infrenced type

	// auto with const
	const std::vector<int> myconstvec2;
	auto myvec2 = myconstvec2;	// when infrencing type of myvec2 variable from type of constmyvec2 variable, const specifier of constmyvec2 variable is removed 
	auto & reftoconstmyvec2 = myconstvec2;

	// auto with volatile
	volatile long clock = 0;
	auto c = clock;	// when infrencing type of c variable from type of clock variable, volatile specifier of clock variable is removed 

	// auto for static arrays
	auto const elems = 42;
	double arronedoubles[5][elems]; // compile error unless elems is of type const
	double arrtwodoubles[elems][5];	// compile error unless elems is of type const
	auto ptrarrone = arronedoubles; // returns ppointer to an array of "elems" elements
	auto ptrarrtwo = arrtwodoubles; // returns ppointer to an array of 5 elements

	// auto for class objects
	someClass objsomeclass;
	//auto obj1 = objsomeclass;		// compile error since class has an explicit copy constructor
	auto obj2 (objsomeclass);		// type of obj2 is "someClass"
	auto & refobj1 = objsomeclass;	// type of refobj1 is "someClass&"

	// auto for function pointers
	auto ptrfunc = globalFunc;		// type of ptrfunc is "void (*)(int, float)"
	auto & reffunc = globalFunc;	// type of reffunc is "void (&)(int, float)"

	auto num = 99;			// type of num is int
	auto numlist = { 99 };	// type of numlist is std::initializer_list<int>

	return 0;
}