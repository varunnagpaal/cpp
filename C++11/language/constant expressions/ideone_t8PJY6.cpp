// constexpr part two
#include <iostream>
using namespace std;


// function-type-qualifier 		func-type	function(	argument-type-qualifier arg-type argument )
// 3(constexpr,const,nothing) 	x						2(const,nothing) = 6

// nothing, nothing
double func1( double a )
{
}
// nothing, const
double func2( const double& a )
{
	return a;
}

// const,nothing
const double& func3( double a )
{
	return a;
}

// const, const
const double& func4( const double& a )
{
	return a;
}
// constexpr, nothing
constexpr double func5( double a )
{
	return a;
}

// constexpr, const
constexpr double func6( const double& a )
{
	return a;
}

int main() 
{
		
	return 0;
}