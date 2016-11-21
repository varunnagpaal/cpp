// Shared pointers and weak pointers
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

// Forward declaration
class ParentNode;

// Class declarations/definitions
class ChildNode
{
	std::unique_ptr<ParentNode> _parent;
};

class ParentNode
{
	private:
		// Each parent has a list of pointers to children
		std::vector<std::unique_ptr<ChildNode>> _children;
};

int main()
{
	return 0;
}