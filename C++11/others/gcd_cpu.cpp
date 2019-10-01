#include <iostream>
#include <chrono>
#include <type_traits>

// Check if high_resolution_clock is steady type. If true, use high_resolution_clock. Otherwise use steady_clock
using SteadyClock = typename std::conditional<std::chrono::high_resolution_clock::is_steady,
															std::chrono::high_resolution_clock,
															std::chrono::steady_clock>::type;
using TimePoint = std::chrono::time_point<SteadyClock>;

void gcd_sw_model (int a, int b, int *pResult )
{
	int result = a;

	while( a != b )
	{
		if( a > b )
		{
			a = a-b;
		}
		else
		{
			b = b-a;
		}
	}
	result = a;
	*pResult = result;
}

auto Timepoint_To_ns(const TimePoint& point) 
{
    using Ns = std::chrono::nanoseconds;
    const SteadyClock::duration since_epoch = point.time_since_epoch();
    return std::chrono::duration_cast<Ns>(since_epoch).count();
}

int main()
{
	int data_in_a=60;
	int data_in_b=36;
	int data_out_res = 0;
	
	int testIterations=10000000;
	
	TimePoint accumTime = TimePoint();
	
	//std::cout << Timepoint_To_ns(accumTime) << " ns\n";	

	std::cout << "[GCD on Intel i7 - 6700HQ CPU core]" << std::endl;
	std::cout << "Running timing test for " << testIterations << " iterations to get average execution time. Please wait for results...." << std::endl;
	for(auto i = 0; i<testIterations ; ++i)
	{
		auto startTime = SteadyClock::now();
		gcd_sw_model(data_in_a, data_in_b, &data_out_res);
		auto endTime = SteadyClock::now();
		accumTime += (endTime - startTime);
	}
	std::cout << "Done!" << std::endl;
	std::cout << "Average GCD execution time on Intel CPU core: " << Timepoint_To_ns(accumTime)/testIterations << " nsec" << std::endl;
}