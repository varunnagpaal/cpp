// Smart pointers
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class someCls
{
		int a_;
		float b_;
		char c_;	

	public:
		someCls(){}
		~someCls(){}
	
		void setA( int a )
		{
			a_ = a;
		}

		void setB( float b )
		{
			b_ = b;
		}
		
		void setC( char c )
		{
			c_ = c;
		}
		
		int getA() const
		{
			return a_;
		}
		
		float getB() const
		{
			return b_;
		}
		
		char getC() const
		{
			return c_;
		}		
};

void TestLegacyFunc(someCls *obj)
{
	std::cout << "a: " << obj->getA() << ", b: " << obj->getB() << ", c: " << obj->getC() << std::endl;
};

void TestPassingUp( std::unique_ptr<int> p)
{
	std::cout << "TestPassingUp() received unique pointer [" << p.get() << "]" << std::endl; 
}

std::unique_ptr<int> TestRetUp()
{ 
	auto up = std::make_unique<int>();
	*up=100;
	std::cout << "TestRetUp() creates unique pointer [" << up.get() << "] with value *up=" << *up << std::endl;
	return std::move(up); // note that std::move is optional here
}

int main() 
{
	// Unique pointer is a class template whose object is created on stack.
	// Unique pointer objects on stack can own maximum one a heap allocated object
	// Replaces auto_ptr, which is deprecated.
	std::unique_ptr<int> up1(new int);
	*up1 = 200;
	std::cout << "*up1: " << *up1 << std::endl;
	
	// Unique pointers cannot be copied or assigned as their copy constructor 
	// and copy assignment operator are deleted functions
	// auto upcpy1 = up1; // compile error
	std::unique_ptr<int> upassgnmove1;
	// upassgnmove1 = up1; // compile error
	
	// Unique pointers can only be moved
	// moving removes ownership of the heap object
	// from the source unique ptr and transfers its ownership 
	// to the destination unique pointer
	upassgnmove1 = std::move(up1);
	
	// std::cout << "*up1: " << *up1 << std::endl; // runtime error
	
	*upassgnmove1 = 21020;
	std::cout << "*upassgnmove1: " << *upassgnmove1 << std::endl;
	
	std::vector<std::unique_ptr<int>> vecups;
	// vecups.push_back( upassgnmove1 ); // compiler error: unique pointers can only be moved
	std::cout << "Moving unique pointer upassgnmove1 [" << upassgnmove1.get() <<"] to vector vecups" <<std::endl;
	vecups.push_back( std::move(upassgnmove1) );
	
	std::cout<< "After move upassgnmove1: " << upassgnmove1.get() << std::endl;
	
	// Passing(moving) unique pointer to a function essentially transfers ownership
	// of resource from caller to called function
	std::cout << "Passing(moving) unique pointer vecups[0]=[" << vecups[0].get()  << "] to TestPassingUp() " << std::endl;
	TestPassingUp( std::move( vecups[0] ) ) ;
	std::cout<< "Unique pointer vecups[0] after it was moved to TestPassingUp(): [" << vecups[0].get() << "]" << std::endl;	
	
	// Returning a unique pointer from a function essentially transfers ownership 
	// of resource from called function to the caller
	auto myUp = TestRetUp();
	
	std::cout << "Unique pointer returned from TestRetUp() is [" << myUp.get() << "] with value *myUp=" << *myUp << std::endl;
	
	// Unique pointer can free and cleanup its resource explicitly through reset
	// or implicitly when unique pointer goes out of scope(even if an exception 
	// is thrown somewhere further up the stack.)
	upassgnmove1.reset();
	
	// Assign new resource to unique pointer
	upassgnmove1.reset( new int);
	*upassgnmove1 = 90;
	std::cout << "*upassgnmove1: " << *upassgnmove1 << std::endl;
	
	// Free and cleanup its existing resource before
	// assigning new resource to unique pointer
	upassgnmove1.reset( new int);
	*upassgnmove1 = 12340;
	std::cout << "*upassgnmove1: " << *upassgnmove1 << std::endl;
	
	// Assign to uniqe pointer the ownership of a class object allocated on heap
	std::unique_ptr<someCls> upclassobj1(new someCls);
	upclassobj1->setA(10);
	upclassobj1->setB(0.9);
	upclassobj1->setC('h');	
	
	// Sizeof unique pointer is sams as sizeof the raw pointer
	std::cout << "sizeof(someCls*): " << sizeof(someCls*) << std::endl;
	std::cout << "sizeof(upclassobj1): " << sizeof(upclassobj1) << std::endl;
	
	// Legacy C/C++ APIs whose interfaces require passing raw pointers
	// can use smart pointer get() function to get raw pointer of owned 
	// resource
	TestLegacyFunc( upclassobj1.get() );
	
	// Shared pointer is a reference counted smart pointer
	// The heap allocated object that shared pointer points to can be 
	// owned by multiple shared pointer stack objects
	// Each such shared pointer stack object keeps a reference count
	// of how many owners the heap allocated object has
	std::shared_ptr<int> sp1(new int);
	std::shared_ptr<int> sp2(sp1);
	*sp1 = -1000;
	std::cout << "*sp1: " << *sp1 << std::endl;
	std::cout << "*sp2: " << *sp2 << std::endl;
	
	// All stack allocated unique pointers when going out of scope call
	// their delete functions to free their respective owned heap objects
}