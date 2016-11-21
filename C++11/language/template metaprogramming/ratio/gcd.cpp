#include "gcd.h"
#include <iostream>

int main()
{
	auto gcd1 = vng::math::gcdDij<10, 7>::value;
	std::cout << "gcddij<10, 7>::value= " << gcd1 << '\n';
	gcd1 = vng::math::gcdDij<10, 5>::value;
	std::cout << "gcddij<10, 5>::value= " << gcd1 << '\n';
	gcd1 = vng::math::gcdDij<10, 0>::value;
	std::cout << "gcddij<10, 0>::value= " << gcd1 << '\n';
	gcd1 = vng::math::gcdDij<0, 5>::value;
	std::cout << "gcddij<0, 5>::value= " << gcd1 << '\n';
	gcd1 = vng::math::gcdDij<0, 0>::value;
	std::cout << "gcddij<0, 0>::value= " << gcd1 << '\n';

	std::cout << '\n';

	gcd1 = vng::math::gcdEucl<10, 7>::value;
	std::cout << "gcdeucl<10, 7>::value= " << gcd1 << '\n';
	gcd1 = vng::math::gcdEucl<10, 5>::value;
	std::cout << "gcdeucl<10, 5>::value= " << gcd1 << '\n';
	gcd1 = vng::math::gcdEucl<10, 0>::value;
	std::cout << "gcdeucl<10, 0>::value= " << gcd1 << '\n';
	gcd1 = vng::math::gcdEucl<0, 5>::value;
	std::cout << "gcdeucl<0, 5>::value= " << gcd1 << '\n';
	gcd1 = vng::math::gcdEucl<0, 0>::value;
	std::cout << "gcdeucl<0, 0>::value= " << gcd1 << '\n';

	system("pause");
	return 0;
}