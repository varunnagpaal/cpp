#pragma once
#include <cstdint>

/*----------- Template metaporgam which implements Dijikstras and Euclids recursive GCD algorithms-----------*/

namespace vng
{
	namespace math
	{
		template <intmax_t N>
		struct _abs
		{
			static intmax_t constexpr value = (N > 0 ? N : -N);
		};

		template <intmax_t A, intmax_t B>
		struct _max
		{
			static intmax_t constexpr value = (A > B ? A : B);
		};

		template <intmax_t A, intmax_t B>
		struct _min
		{
			static intmax_t constexpr value = (A < B ? A : B);
		};

		// Dijikstras GCD algorithm
		// gcd(a,b) = a if a == b
		//			= gcd(a-b,b) if a>b
		//			= gcd(a,b-a) if b>a
		template < intmax_t A, intmax_t B >
		struct gcdDij
		{
			static intmax_t constexpr value = gcdDijImpl< _abs<A>::value, _abs<B>::value >::value;
		};

		template < intmax_t A, intmax_t B >
		struct gcdDijImpl
		{
			static intmax_t constexpr calc(intmax_t a, intmax_t b)
			{
				/* Error as constanetxpr function can have only single line of code which is return statement
				if (a == b)
				{
				return a;
				}
				else if (a > b)
				{
				return calc(a - b, b);
				}
				else
				{
				return calc(a, b-a);
				}
				*/

				return (a == b ? a : (a > b ? calc(a - b, b) : calc(a, b - a)));
			}
			static intmax_t constexpr value = calc(A, B);
		};


		// Euclids GCD algorithm
		// For a >= b > 0
		// gcd(a,b) = b if a % b == 0
		//			= gcd(b,a) otherwise
		template < intmax_t A, intmax_t B >
		struct gcdEucl
		{
			static intmax_t constexpr value = gcdEuclImpl< _max< _abs<A>::value, _abs<B>::value >::value,
				_min< _abs<A>::value, _abs<B>::value >::value >::value;
		};

		template < intmax_t A, intmax_t B >
		struct gcdEuclImpl
		{
			static intmax_t constexpr calc(intmax_t a, intmax_t b)
			{
				/* Error as constanetxpr function can have only single line of code which is return statement
				if ( ( a % b ) == 0 )
				{
					return b;
				}
				else
				{
					return calc( b, a % b );
				}
				*/

				return ((a % b) == 0 ? b : calc(b, a % b));
			}
			static intmax_t constexpr value = calc(A, B);
		};

		// Special base cases
		template < intmax_t A  >
		struct gcdDijImpl<A, 0>
		{
			static intmax_t constexpr value = A;
		};

		template < intmax_t A  >
		struct gcdDijImpl<0, A>
		{
			static intmax_t constexpr value = A;
		};

		template <>
		struct gcdDijImpl<0, 0>
		{
			static intmax_t constexpr value = 1;
		};

		template < intmax_t A >
		struct gcdEuclImpl<A, 0>
		{
			static intmax_t constexpr value = A;
		};

		template < intmax_t A >
		struct gcdEuclImpl<0, A>
		{
			static intmax_t constexpr value = A;
		};

		template <>
		struct gcdEuclImpl<0, 0>
		{
			static intmax_t constexpr value = 1;
		};
	}
}