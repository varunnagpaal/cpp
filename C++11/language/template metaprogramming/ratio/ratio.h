#pragma once
#include <cstdint>
#include "gcd.h"

/* Ratio class template defined on the lines of stl <ratio>
   Note: this class is still incomplete: 
    - missing type traits to check if type is a ratio
	- overflow/underflow check
	- optimizations, etc.
*/

namespace vng
{
	namespace math
	{
		// Main Ratio template class
		template<intmax_t N, intmax_t D>
		struct ratio
		{
			static_assert(D != 0, "Denominator cannot be zero in a ratio");

			// Normalize the ratios
			static intmax_t constexpr n = N / gcdDij<N, D>::value;
			static intmax_t constexpr d = D / gcdDij<N, D>::value;

			using type = typename ratio<n, d>::type;
		};

		/* Helper functions defined on a ratio */

		// Check if given type is a ratio type at compile-time
		// Use type traits
		template< typename R>
		struct _isRatio // TBU
		{

		};

		/* Basic Arithmetic operations defined on two ratios */

		// Multiply ratios
		template< typename R1, typename R2>
		struct multiply_ratios
		{
			static intmax_t constexpr n1 = R1::n;
			static intmax_t constexpr d1 = R1::d;
			static intmax_t constexpr n2 = R2::n;
			static intmax_t constexpr d2 = R2::d;

			using type = typename ratio<n1*n2, d1*d2>::type;
		};

		// Divide ratios
		template< typename R1, typename R2>
		struct divide_ratios
		{
			static intmax_t constexpr n1 = R1::n;
			static intmax_t constexpr d1 = R1::d;
			static intmax_t constexpr n2 = R2::n;
			static intmax_t constexpr d2 = R2::d;

			using type = typename ratio<n1*d2, n2*d1>::type;
		};

		// Add ratios
		template< typename R1, typename R2>
		struct add_ratios
		{
			static intmax_t constexpr n1 = R1::n;
			static intmax_t constexpr d1 = R1::d;
			static intmax_t constexpr n2 = R2::n;
			static intmax_t constexpr d2 = R2::d;

			using type = typename ratio<n1*d2 + n2*d1, d1*d2>::type;
		};

		// Substract ratios
		template< typename R1, typename R2>
		struct subtract_ratios
		{
			static intmax_t constexpr n1 = R1::n;
			static intmax_t constexpr d1 = R1::d;
			static intmax_t constexpr n2 = R2::n;
			static intmax_t constexpr d2 = R2::d;

			using type = typename ratio<n1*d2 - n2*d1, d1*d2>::type;
		};

		/* Basic Logical operations defined on two ratios */

		// Ratio equality
		template< typename R1, typename R2>
		struct ratio_equal
		{
			static bool constexpr value = ((R1::n == R2::n) && (R1::d == R2::d) ? true : false);
		};

		// Ration unequal
		template< typename R1, typename R2>
		struct ratio_unequal
		{
			static bool constexpr value = ((R1::n != R2::n) || (R1::d != = R2::d) ? true : false);
		};

		// Ratio greater than
		template< typename R1, typename R2>
		struct ratio_greater
		{
			static bool constexpr value = ((R1::n * R2::d) > (R1::d * R2::n) ? true : false);
		};

		// Ratio greater than or equal to
		template< typename R1, typename R2>
		struct ratio_greater_equal
		{
			static bool constexpr value = ((R1::n * R2::d) >= (R1::d * R2::n) ? true : false);
		};

		// Ratio less than
		template< typename R1, typename R2>
		struct ratio_less
		{
			static bool constexpr value = ((R1::n * R2::d) < (R1::d * R2::n) ? true : false);
		};

		// Ratio less than or equal to
		template< typename R1, typename R2>
		struct ratio_less_equal
		{
			static bool constexpr value = ((R1::n * R2::d) <= (R1::d * R2::n) ? true : false);
		};

		// Pre-defined ratios (Standard and Indian)
		using atto = ratio<1, 1000000000000000000LL>;
		using femto = ratio<1, 1000000000000000LL>;
		using pico = ratio<1, 1000000000000LL>;

		using nano = ratio<1, 1000000000>;
		using micro = ratio<1, 1000000>;
		using milli = ratio<1, 1000>;
		using centi = ratio<1, 100>;
		using deci = ratio<1, 10>;
		using deca = ratio<10, 1>;
		using hecto = ratio<100, 1>;
		using kilo = ratio<1000, 1>;
		using mega = ratio<1000000, 1>;
		using giga = ratio<1000000000, 1>;

		using hazaar = kilo;
		using lakh = ratio<100000, 1>;
		using crore = ratio<10000000, 1>;
		using arab = giga;
		using kharab = ratio<100000000000LL, 1>;

		using tera = ratio<1000000000000LL, 1>;
		using peta = ratio<1000000000000000LL, 1>;
		using exa = ratio<1000000000000000000LL, 1>;
	}
}