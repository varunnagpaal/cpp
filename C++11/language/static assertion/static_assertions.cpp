#include <cassert>
#include <type_traits>
#include <limits>
#include <string>

class X
{

};
template<typename T, unsigned int val>
class test
{
	T x, y;

public:
	test()
	{
		static_assert(std::is_arithmetic<T>::value, "Only integer or floating types are supported");
		static_assert(val < 1000, "value must be less than 1000");
	}
};

constexpr double speed_of_light = 300000000.00;

int main()
{
	// Runtime assertions
	// Requires header: assert.h or cassert (c++)
	// recommended only in debug builds
#ifdef _DEBUG
	assert(11 == 11);
#endif

	// C++11 compile time assertions
	// Language based so requires no header file
	// Recommended over runtime assertions
	static_assert(sizeof(int) == 4, "size of int is not 4!");
	static_assert(sizeof(short int) == sizeof(int), "Not expecting short int and int to be of same size");
	static_assert(sizeof(double) == sizeof(int), "Not expecting double and int to be of same size");

	// static assert used for validating template parameter types
	test<int, 2000> tint1;
	test<float, 9999> tfloat1;
	test<X, 1> tchar1;

	constexpr double localspeed1 = 1000 / 15;
	constexpr double localspeed2 = 5000000000 / 15;

	static_assert(localspeed1 < speed_of_light, "should be smaller then speed of light");
	static_assert(localspeed2 < speed_of_light, "should be smaller then speed of light");
	return 0;
}