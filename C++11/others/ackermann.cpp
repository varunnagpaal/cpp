#include <iostream>
#include <chrono>
#include <type_traits>
#include <tuple>
#include <string>

// Check if high_resolution_clock is steady type. If true, use high_resolution_clock. Otherwise use steady_clock
using Ns = std::chrono::nanoseconds;
using SteadyClock = typename std::conditional<std::chrono::high_resolution_clock::is_steady,
	std::chrono::high_resolution_clock,
	std::chrono::steady_clock>::type;
using TimePoint = std::chrono::time_point<SteadyClock>;

struct PreComputed_t
{
	uint64_t result;
	bool isCalculated;
};

struct ExecTimeTable_t
{
	uint64_t m;
	uint64_t n;
	uint64_t result;
	uint64_t iterations;
	TimePoint accumExecTimePoints;
	uint64_t avgExecTime_ns;
};

PreComputed_t preComputedResults[100][100];

auto Timepoint_To_ns(const TimePoint& point)
{
	
	const SteadyClock::duration since_epoch = point.time_since_epoch();
	return std::chrono::duration_cast<Ns>(since_epoch).count();
}

uint64_t ack_cpu_model(uint64_t const m, uint64_t const n)
{
	// A(m,n) = n+1					if m = 0
	//			A(m-1, 1)			if m > 0 and n = 0 
	//			A(m-1, A(m,n-1))	if m > 0 and n > 0 

	if (0 == m) { return n + 1; }
	else if (m > 0 && 0 == n) { return ack_cpu_model(m - 1, 1); }
	else { return ack_cpu_model(m - 1, ack_cpu_model(m, n - 1)); }
}

int main()
{
	uint64_t m_in;
	uint64_t n_in;
	
	const uint64_t M_MAX = 100;
	const uint64_t N_MAX = 100;
	ExecTimeTable_t execTimeTable[M_MAX][N_MAX];

	std::cout << "[Ackermann Function A(m, n) on Intel i7 - 6700HQ CPU core]" << std::endl;

	do {
		std::cout << "Enter m (<=" << M_MAX << "): ";
		std::cin >> m_in;
	} while (m_in > M_MAX);


	do {
		std::cout << "Enter n (<=" << N_MAX << "): ";
		std::cin >> n_in;
	} while (n_in > N_MAX);

	for (uint64_t m = 0; m <= m_in; ++m)
	{
		for (uint64_t n = 0; n <= n_in; ++n)
		{
			execTimeTable[m][n].m = m;
			execTimeTable[m][n].n = n;
			execTimeTable[m][n].result = 0;
			execTimeTable[m][n].iterations = (m <= 4) ? 1 : 1;
			execTimeTable[m][n].accumExecTimePoints = TimePoint();
			execTimeTable[m][n].avgExecTime_ns = 0;
			
			uint64_t testIterations = execTimeTable[m][n].iterations;
			std::cout << "Running timing test for A(" << m << "," << n << ") for " << testIterations << " iterations to get average execution time. Please wait for results....";
			std::cout.flush();

			TimePoint accumTime = TimePoint();
			//std::cout << Timepoint_To_ns(accumTime) << " ns\n";
			uint64_t result;
			for (uint64_t i = 0; i < testIterations; ++i)
			{
				auto startTime = SteadyClock::now();
				result = ack_cpu_model(m, n);
				auto endTime = SteadyClock::now();
				accumTime += (endTime - startTime);
			}
			execTimeTable[m][n].result = result;
			execTimeTable[m][n].accumExecTimePoints = accumTime;
			execTimeTable[m][n].avgExecTime_ns = Timepoint_To_ns(accumTime) / testIterations;
			std::cout << "Done!" << std::endl;
		}
	}

	std::cout << "Summry of Average execution time of Ackermann Function on single Intel CPU core" << std::endl;
	std::cout << "m\tn\tA(m,n)\tIterations\tAverage Execution Time(ns)" << std::endl;

	for (uint64_t m = 0; m <= m_in; ++m)
	{
		for (uint64_t n = 0; n <= n_in; ++n)
		{
			std::cout << m << "\t" 
					  << n << "\t" 
					  << execTimeTable[m][n].result << "\t"
					  << execTimeTable[m][n].iterations << "\t\t"
					  << execTimeTable[m][n].avgExecTime_ns << std::endl;
		}
	}

}