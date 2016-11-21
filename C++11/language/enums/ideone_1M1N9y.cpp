// 	Enum classes or scoped enums
#include <iostream>
#include <string>

// forward declare scoped enums
enum class myNewEnum;

//cannot forward declare scoped enum
// gives following error: error: use of enum 'myOldEnum' without previous declaration
//enum myOldEnum;

class UseEnumUndeclared
{
	private:
	public:
		void UseNewEnumUndefined( myNewEnum en );
		//void UseOldEnumUndefined( myOldEnum );
	
};

int main() {
	// your code goes here
	enum OldStyleMyEnum { a,b,c,d};
	
	// shows following error: error: 'auto b' redeclared as different kind of symbol
	// auto b = 1.0909034; // error due to leaking of enum member a into current scope
	
	std::cout << "Leaked name: " << b << std::endl;
	
	enum class NewStyleScopedEnumClass{ h,i,j,k};
	auto i = "hello";
	NewStyleScopedEnumClass	anenum = NewStyleScopedEnumClass::i;
	std::cout << "NonLeaked name: " << static_cast<unsigned>(anenum) << std::endl;
	std::cout << "Normal scope variable: " << i << std::endl;
	
	return 0;
}