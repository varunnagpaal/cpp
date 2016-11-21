#include <iostream>
using namespace std;

class BaseA
{
	public:
		BaseA();
		~BaseA();
		void doNothing();
};

void BaseA::doNothing()
{
	
}

class DerivedA: private BaseA
{
	public:
	 	DerivedA();
	 	~DerivedA();
};


int main() {
	//BaseA *ptrBaseObj = new BaseA();
	//DerivedA *ptrDerivedObj = new DerivedA();
	 BaseA obj;
	//delete ptrBaseObj;
	//delete ptrDerivedObj;
	
	return 0;
}