#include <chrono>
#include <iostream>
#include <type_traits>

using namespace std::literals::chrono_literals; // for literals such as h,m,s for hours, minutes, seconds

// Check if high_resolution_clock is steady type. If true, use high_resolution_clock. Otherwise use steady_clock
using SteadyHighResolutionClock = typename std::conditional<std::chrono::high_resolution_clock::is_steady,
															std::chrono::high_resolution_clock,
															std::chrono::steady_clock>::type;

template <typename C>
void printClockData()
{
	using namespace std;
	cout << "- precision: ";
	// if time unit is less or equal one millisecond
	typedef typename C::period P; // type of time unit
	if (ratio_less_equal<P, milli>::value) {
		// convert to and print as milliseconds
		typedef typename ratio_multiply<P, kilo>::type TT;
		cout << fixed << double(TT::num) / TT::den
			<< " milliseconds" << endl;
	}
	else {
		// print as seconds
		cout << fixed << double(P::num) / P::den << " seconds" << endl;
	}
	cout << "- is_steady: " << boolalpha << C::is_steady << endl;
}

void printTimeNano( std::chrono::nanoseconds ns )
{
	std::cout << ns.count() << '\n';
}

int main( int argc, char *argv[])
{
	// --------Time scales in chrono ---- 
	//std::chrono::nanoseconds timeErrNano = 100;
	std::chrono::nanoseconds timeNoInitNano;
	std::chrono::nanoseconds timeEmptyNano{};
	std::chrono::nanoseconds timeInitNano{ 100 };
	std::cout << timeNoInitNano.count() << '\n';
	std::cout << timeEmptyNano.count() << '\n';
	std::cout << timeInitNano.count() << '\n';

	// custom ratios (types)
	using Day = std::ratio_multiply< std::chrono::hours::period, std::ratio<24, 1> >::type;
	using Year = std::ratio_multiply< Day, std::ratio<365, 1> >::type;
	using LeapYear = std::ratio_multiply< Day, std::ratio<366, 1> >::type;

	// custom ratios (types) as per Indian System
	using Lakh_t = std::ratio<100000, 1>::type;
	using Crore_t = std::ratio<10000000, 1>::type;
	using Arab_t = std::ratio<1000000000, 1>::type;
	using Kharab_t = std::ratio<100000000000, 1>::type;

	// defining custom time duration types
	using LakhVarsh_t = std::chrono::duration<intmax_t, std::ratio_multiply<Lakh_t,Year> >;
	using CroreVarsh_t = std::chrono::duration<intmax_t, std::ratio_multiply<Crore_t,Year>>;
	using ArabVarsh_t = std::chrono::duration<intmax_t, std::ratio_multiply<Arab_t,Year>>;
	using KharabVars_t = std::chrono::duration<intmax_t, std::ratio_multiply<Kharab_t,Year>>;

	// 2 lakhvarsh time
	LakhVarsh_t twolakhvarsh{ 2 };

	// duration constructor can be used to convert between duration types
	// as long as conversion doesn't require truncation. 
	// For example here we conver 2 lakhvarsh duration into seconds which doesnt 
	// require truncation
	std::chrono::seconds secondsintwolakhvarsh(twolakhvarsh); 
	std::cout << "twolakhvarsh seconds = " << secondsintwolakhvarsh.count() << '\n';

	// However converting seconds into hours will require truncation.
	// For example 2000 seconds = 33.33 minutes = 0.55 hours and hence requires truncation
	// note that truncation may also be required when converting hours to seconds such as 0.33 hours 
	// to seconds will require truncation
	// and thus we cant use constructor to do this. 
	
	//compilation error when converting using a constructor as it requires truncation
	//std::chrono::hours myhours(2000s);
	//std::chrono::hours twolakhvarshhours(secondsintwolakhvarsh);

	// So for conversions between durations that require truncation 
	// we need to use a duration cast instead of constructor
	const auto myhours = std::chrono::duration_cast<std::chrono::hours>(2000s);
	const auto twolakhvarshhours = std::chrono::duration_cast<std::chrono::hours>(secondsintwolakhvarsh);
	const auto mytwolakhvarsh = std::chrono::duration_cast<LakhVarsh_t>(secondsintwolakhvarsh);
	
	const std::chrono::seconds firstsecs(2h);
	// const std::chrono::seconds secondsecs(2.5h); // compilation error since truncation required
	const auto mysecs = std::chrono::duration_cast<std::chrono::seconds>(2.5h);

	// It is allowed to create arithmetic expressions involving durations of different time units
	// This is due to the provided overloading of common_type<> for durations, the resulting duration
	// will have a unit that is the greatest common divisor of the units of both operands.
	const auto mymins = std::chrono::duration_cast<std::chrono::minutes>((12min + .5h) / 2 + (100ns >= 1ms ? -3h : ++59s));
	std::cout << "duration_cast<minutes>((12min + .5h) / 2 + (100ns >= 1ms? -3h : ++59s)): " << mymins.count() << '\n';

	// It is allowed to compare two durations with different time units
	// Here we compare durations with time units LakhVarsh and seconds
	if (mytwolakhvarsh == secondsintwolakhvarsh)
	{
		std::cout << "Conversion between durations(2 lakh years vs 2 lakh years in seconds)  doesnt change the fact that they can be compared(here they are equal)" << '\n';
	};

	if (mytwolakhvarsh.count() != secondsintwolakhvarsh.count() )
	{
		std::cout << "However there counts may be different" << '\n';
	}

	// Using an in-built steady clock in chrono
	// now() for a clock returns current time tick also called time_point
	std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now(); 

	// printTimeNano(100); // error compilation
	printTimeNano(timeInitNano);
	printTimeNano(std::chrono::nanoseconds{79});

	// Duration is time elapsed between two time ticks or time_points obtained from same clock
	std::chrono::steady_clock::duration duration = std::chrono::steady_clock::now() - t;
	std::cout << "Time taken: " << duration.count() << '\n';

	std::chrono::microseconds us(1000000000000LL);

	// Splitting time in hours, minutes, seconds, milliseconds, microseconds
	std::chrono::hours hrs = std::chrono::duration_cast<std::chrono::hours>(us);
	std::chrono::minutes mins = std::chrono::duration_cast<std::chrono::minutes>(us % std::chrono::hours(1));
	std::chrono::seconds secs = std::chrono::duration_cast<std::chrono::seconds>(us % std::chrono::minutes(1));
	std::chrono::milliseconds msecs = std::chrono::duration_cast<std::chrono::milliseconds>(us % std::chrono::seconds(1));
	std::chrono::microseconds usecs = std::chrono::duration_cast<std::chrono::microseconds>(us % std::chrono::milliseconds(1));

	std::cout << us.count() << "ms ==" 
			  << hrs.count() << "hrs "
			  << mins.count() << "mins "
			  << secs.count() << "secs "
			  << msecs.count() << "msecs "
			  << usecs.count() << "usecs "
			  << '\n';

	// Epoch, Timepoint and Clock
	// Epoch is the reference point in time relative to which a clock shows elapsed time. Epoch for different clock is different.
	// A timepoint is simply a point in time relative to epoch of its particular clock expressed as duration of time (hours,seconds etc.)
	// Epoch for a clock thus can also be defined as zero timepoint

	std::chrono::time_point<std::chrono::system_clock, std::chrono::hours> hunHrSinceSysClkEpoch(100h);
	std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes> hunMinsSinceSteadyClkEpoch = hunHrSinceSysClkEpoch;

	// Subtracting two time points results in duration
	auto elapsedDuration = (hunHrSinceSysClkEpoch - hunMinsSinceSteadyClkEpoch);
	std::cout << elapsedDuration.count() << '\n';

	// Just like durations with different time units can be explicitly and implcitly casted, 
	// we can also cast time points with different duration types 
	auto hrsSinceEepoch1 = std::chrono::time_point_cast<std::chrono::hours>(hunMinsSinceSteadyClkEpoch);					// explicit
	std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> secSinceEpoch1 = hunMinsSinceSteadyClkEpoch;	// implicit

	// Clock
	// A clock can be steady or unsteady. A steady clock is guranteed to be monotonic i.e. it always proceeds
	// and cant be adjusted i.e. given two consecutive time points t1 and t2, it is guranteed t1 <= t2. 
	// Unsteady clock may be adjusted so it may be non-monotonic
	// A clock has a now() member function which yields current time point (of type timepoint) at moment of call
	// A clock has internal typedefs to represent type of its duration<rep, period>, timepoint
	// STL has three clocks: 
	//	1. steady_clock(guaranteed to be monotonic),
	//	2. system_clock(corresponds to real time clock of system hardware),
	//  3. high_resolution_clock(clock with smallest period supported on the system)

	// Print clock details on this machine
	std::cout << "system_clock: " << std::endl;
	printClockData<std::chrono::system_clock>();
	std::cout << "\nhigh_resolution_clock: " << std::endl;
	printClockData<std::chrono::high_resolution_clock>();
	std::cout << "\nsteady_clock: " << std::endl;
	printClockData<std::chrono::steady_clock>();


	// Lets time some operation
	// To time an operation, always use clock which is steady and highest resolution possible
	std::cout << "Using high_resolution_clock" << '\n';
	auto start = SteadyHighResolutionClock::now();
	auto k = 0;
	for (auto i = 0; i < INT32_MAX; ++i)
	{
		k += (i * 3);
	}
	auto elap = (std::chrono::high_resolution_clock::now() - start);
	std::cout << "Time taken to Multiply-Accumulate " << INT32_MAX << " numbers is " << elap.count() << '\n';


	system("pause");
	return 0;
}
