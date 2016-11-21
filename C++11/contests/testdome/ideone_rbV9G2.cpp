#include <iostream>
#include <stdexcept>

class Frog
{
	static const int rest = 0;
	static const int step = 1;
	static const int jump = 2;
public:

	static int factorial( int number )
	{
		int result=1;
		for(; number > 1 ; --number )
		{
			result *= number; 
		}
		
		return result;
	}
	static int numberOfWays(int n)
	{
		int countWays = 0;
		if( n <= 0 )
		{
			countWays = 0;
		}else if( n == step )
		{
			countWays = 1;
		}else
		{
			// x*step + y*jump = n
			// we have to find all (x,y) integer pairs i.e permutations
			// for which above equation is true
			for( int x = 0; x <= n ; ++x )
			{
				for( int y = 0 ; y <= n ; ++y )
				{
					if( n == (x*step+y*jump))
					{
						std:: cout << x << " * step + " << y  << " * jump = " << n << std::endl;
						if( x ==0 || y == 0 )
						{
							countWays += 1;
						}
						else
						{
							countWays += factorial(x+y)/(factorial(x)*factorial(y));
						}
					}
				}
			}			
		}
		
		return countWays;
	}
};

int main(int argc, const char* argv[])
{
	std::cout << Frog::numberOfWays(4);
	return 0;
}