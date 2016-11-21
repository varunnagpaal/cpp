#include <iostream>

class baseClass
{
public:
	void nonVirtFunc() {}
};

class baseVirtClass
{
public:
	void nonVirtFunc() { std::cout << "Base nonVirtFunc" << '\n'; }
	virtual void virtFunc1() { std::cout << "Base virtFunc1" << '\n'; }
	virtual void virtFunc2() { std::cout << "Base virtFunc2" << '\n'; }
};

class baseNewVirtClass
{
public:
	virtual void someVirtFunc() {}
};

class derivedOverridingClass : public baseVirtClass
{
public:
	virtual void virtFunc1() { std::cout << "Overriding virtFunc1:" << '\n'; }
};

class derivedNonOverridingClass : public baseVirtClass
{
	// We donot override any base class virtual functions here
};

class derivedOverrideMultipleInherit : public baseVirtClass, baseNewVirtClass
{

};

int main(int argc, char *argv[])
{
	baseClass baseClassObj1;
	std::cout << "Sizeof object of class with non virtual functions: " << sizeof(baseClassObj1) << '\n';

	// Objects of a class with virtual functions will have a vfptr(type void**)
	// which points to same vftable object storing array of function pointers(void*)
	baseVirtClass baseVirtClassObj1;
	baseVirtClass baseVirtClassObj2;
	std::cout << "Sizeof object of class with virtual functions: " << sizeof(baseVirtClassObj1) << '\n';
	std::cout << "Sizeof object of class with virtual functions: " << sizeof(baseVirtClassObj2) << '\n';

	// Object of derived class overrding some virtual functions of base class
	// will have a vfptr which points to a different vftable object than in vfptr base class
	// This vftable stores array of function pointers. Functions which are 
	// not overrriden in derived class will have same address as that of virtual functions in vftable 
	// of base class. Virtual functions which are overridden in derived class, they will 
	// have a different function pointer in vftable of derived class then function pointer of this function
	// in base class
	derivedOverridingClass derOverridingClassObj;
	derOverridingClassObj.nonVirtFunc();
	derOverridingClassObj.virtFunc1();
	derOverridingClassObj.virtFunc2();

	// Derived class which doen't override any base class virtual functions
	// In such a case, again vfptr will store address of a vftable different than 
	// that in base class objects, however as no base class virtual functions are overriden
	// in derived class, this vftable will store function pointers identical to the
	// function pointers in base class object
	derivedNonOverridingClass derNonOverridingClassObj;
	derNonOverridingClassObj.nonVirtFunc();
	derNonOverridingClassObj.virtFunc1();
	derNonOverridingClassObj.virtFunc2();

	// set a breakpoint at return statement and observe local variables 
	// in debug mode to see blue print of base class and derived class objects
	// and how they contain __vfptr pointing to vftable
	return 0;
}