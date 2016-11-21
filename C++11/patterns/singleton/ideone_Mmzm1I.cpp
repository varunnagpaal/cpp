// Create a Thread safe Singleton Class which allows 
// allows user to access per thread local singleton
// instances i.e. each thread can access only its local
// object instance and those local instances are not shared 
// among threads
#include <iostream>
#include <unordered_map>
#include <vector>
#include <thread>
#include <algorithm>
#include <mutex>
#include <memory>
using namespace std;

class single
{
public:
    /// Every thread needs to call this to get its individual instance
	static single* getInstance( unsigned int threadId );
	static void print( unsigned int threadId );
	
protected:
	/// Made protected not private so
	/// that singleton may be subclassed
	/// but cannot be instantiated
	single() = default;							// Clients cant construct objects
	~single() = default;						// Cannot be destroyed by clients holding pointer to singleton object by calling destructor explicitly

	single(const single &) = delete;			// non-copyable
	single& operator=(const single &) = delete;	// can't be copy assigned
	single(single &&) = delete;					// non-move constructible
	single & operator=(single && ) = delete;	// non-move assignable
	
private:
	static std::unordered_map<unsigned,single*> _instances;
	static std::mutex _lock;
};

// Initialize static member variables
std::mutex single::_lock;
std::unordered_map<unsigned,single*> single::_instances;

// Member functions
void single::print( unsigned int threadId )
{
	std::cout << "threadId:"	<< threadId << ", Singleton: " << _instances[threadId] << std::endl;
}

single* single::getInstance( unsigned int threadId )
{
	std::lock_guard<std::mutex> lg(_lock);
	if( _instances.count( threadId ) == 0 )
	{
		_instances[threadId] = new single;
		std::cout <<"Created By ThreadId: " << threadId <<std::endl;
	}

	return _instances[threadId];
}

void Run( unsigned int threadId )
{
	single::getInstance(threadId)->print(threadId);
}

int main()
{
	// higher number of threads causes resource problems with ideone
	const unsigned threadCount = 8;
	std::vector<std::thread> workers;

	for( auto i = 0; i != threadCount; ++i )
	{
		workers.push_back( std::thread( Run, i ) );
	}
	
	for_each( workers.begin(),
			  workers.end(),
			  std::mem_fn(&thread::join) );
	
	return 0;
}