#include <ratio>
#include <iostream>

int main()
{
	// Ratio std::ratio<num,den=1> is num/den. By default den is set to 1 u64. den !=0
	// It defines compile time fractions by encoding num and den of a rational number 
	// as value template arguments
	// Generally raio itself is used as type arguments for other templates
	const int num = 10;
	const int denom = 7;
	
	std::ratio<num, denom> tenbyseven;
	std::cout << "10/7=" << tenbyseven.num << "/" << tenbyseven.den << '\n';

	// Standard ratios defined in in <ratio> as per SI 
	std::deca mydeca;	// ratio<10,1>
	std::hecto myhecto;	// ratio<100,1>
	std::kilo mykilo;	// ratio<1000,1>
	std::mega mymega;	// ratio<1000000,1>
	std::giga mygiga;	// ratio<1000000000,1>
	std::tera mytera;	// ratio<1000000000000,1>
	std::peta mypeta;	// ratio<1000000000000000,1>
	std::peta myexa;	// ratio<1000000000000000000,1>
	std::deci mydeci;	// ratio<1,10>
	std::centi mycenti; // ratio<1,100>
	std::milli mymilli;	// ratio<1,1000>
	std::micro mymicro;	// ratio<1,1000000>
	std::nano mynano;	// ratio<1,1000000000>
	std::pico mypico;	// ratio<1,1000000000000>
	std::femto myfemto;	// ratio<1,1000000000000000>
	std::atto myatto;	// ratio<1,1000000000000000000>


	std::ratio<100, 20> ratio1;	// internally 100/20 is normalized to 5/1 by dividing num and den by gcd(num,den)=20
	std::ratio<15,35> ratio2;	// internally 15/35 is normalized to 3/7 by dividing num and den by gcd(num,den)=5
	std::ratio<5, 2> ratio3;

	std::ratio<100, 64>::type twentyfive_over_sixteen;	// 100/64 normalized to 25/16 and its internal type uses these rationalized type

	// In-built compile time arithmetic & logical operations are defined on
	// ratios but there results are stored as template types
	// this is an example of template metaprogramming because computation is performed at compile time using templates
	std::ratio_add< std::ratio<100, 35>, std::ratio<12, 15>>::type summed_ratios; // 100/35 = 20/7. 12/15=4/5. 20/7+4/5 = 128/35
	std::ratio_subtract<std::ratio<100, 35>, std::ratio<12, 15>>::type subtracted_ratios;
	std::ratio_multiply<std::ratio<100, 35>, std::ratio<12, 15>>::type multiplied_ratios;
	std::ratio_divide<std::ratio<100, 35>, std::ratio<12, 15>>::type divided_ratios;

	if (std::ratio_equal < std::ratio<100, 25>, std::ratio<8, 2> >::value)
	{
		std::cout << "ratios 100/25 is same as ration 8/2" << '\n';
	}

	system("pause");
	return 0;
}