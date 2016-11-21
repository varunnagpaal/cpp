// Smart Pointers - make_shared, make_unique
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;

class someCls
{
	std::string key;
	
public:
	static unsigned count;
	someCls()
	{
		std::cout << ++count << ": Created without key" << std::endl;
	}
	
	someCls(  std::string _key ): key(_key)
	{
		std::cout << ++count << ": Created with key: " << key << std::endl;
	}
	
	~someCls()
	{
		std::cout << --count << ": Deleted" << std::endl;
	}
	
	void Print()
	{
		std::cout << count << ": Hello with key: " << key << std::endl;
	}
};

unsigned someCls::count = 0;

int main() 
{
	// Unique pointer using new
	std::unique_ptr<someCls> up1womake(new someCls);
	
	// Unique pointer using make_unique
	std::unique_ptr<someCls> up1wmake = std::make_unique<someCls>("up1wmake");
	
	up1womake->Print();
	up1wmake->Print();
	
	// Unique pointer ownership transfer
	auto up2womake = std::move( up1womake );
	auto up2wmake = std::move( up1wmake );
	
	up2womake->Print();
	up2wmake->Print();
	
	// Swap unique pointers
	std::swap( up2womake, up2wmake );
	
	// Release ownership of the heap object from the unique pointer
	someCls *up2womakerelease = up2womake.release();
	someCls *up2wmakerelease = up2wmake.release();
	
	// just using unique pointer object decays to bool (true if non-nullptr, false if nullptr )
	if( !up2womake ) std::cout<< "up2womake released ownership its heap object" << std::endl;
	
	// get() function gets the raw pointer to the resource owned by unique pointer
	if( up2wmake.get() == nullptr ) std::cout<< "up2wmake released ownership its heap object" << std::endl;
	
	// Array of uninitialized 5 integers on heap using unique pointer and make_unique
	auto const size = 5;
	auto up1array1 = std::make_unique<int[]>(size);
	
	// initialize array elements
	for( auto i=0;i !=size ; ++i ) up1array1[i] = i*2;
	for_each( up1array1.get(), 	
		  	  up1array1.get() + size,
		  	  [](int & upobj ){ ++upobj; } );
	
	// print array
	std::cout << "Array[" << size << "]: ";
	for_each( up1array1.get(), 
			  up1array1.get() + size,
			  [](int upobj){ std::cout << upobj << ", "; } );
	
	std::cout << std::endl;

	// Shared pointer using new
	std::shared_ptr<someCls> sp1womake(new someCls("sp1womake"));
	std::shared_ptr<someCls> sp2womake = sp1womake;
	
	sp1womake->Print();
	sp2womake->Print();
	
	// Shared pointer using make_shared
	auto sp1wmake = std::make_shared<someCls>("sp1wmake");
	auto sp2wmake = sp1wmake;
	
	sp1wmake->Print();
	sp2wmake->Print();
	
	std::cout << "sp1wmake  reference count:" << sp1wmake.use_count() << std::endl;
	std::cout << "sp2wmake  reference count:" << sp2wmake.use_count() << std::endl;
	
	auto upnew = std::make_unique<int>();
	*upnew =10;
	
	// Shared pointer from a Unique pointer
	// This essentially releases ownership of the resource
	// from unique ptr and transfers it to shared ptr
	// Move-construct a shared pointer from unique pointer
	std::shared_ptr<int> spnew(std::move( upnew ));
	std::cout << "upnew[" << upnew.get() << "]\n";
	std::cout << "spnew[" << spnew.get() << "]: " << *spnew << ". Use count:" << spnew.use_count() << std::endl;
	
	delete up2wmakerelease;
	delete up2womakerelease;
	return 0;
}