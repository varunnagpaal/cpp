#include <iostream>
using namespace std;


class Parsebase
{
	public:
	
	protected:
		virtual void Load() = 0;
		
	private:
};

class Agglomerate: private Parsebase
{
	public:
	protected:
	private:	
};

int main()
{
	Agglomerate a;
	a.Load();
	return 0;
}