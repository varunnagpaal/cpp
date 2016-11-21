#include <iostream>
#include <string>

class myCls
{
	private:
		bool IsStateA( int id )
		{ 
			bool retvalue = false; 
			if( id < 10 ) { retvalue = true; }
			return retvalue;
		}
				
			
		bool IsStateB( int id )
		{ 
			bool retvalue = false; 
			if( id >= 10  && id < 20 ) { retvalue = true; }
			return retvalue;
		}
		
		bool IsStateC( int id )
		{ 
			bool retvalue = false; 
			if( id > 20 ) { retvalue = true; }
			return retvalue;
		}		

		template<typename FuncIsX, typename FuncIsY >
		void PrintIfXorY( FuncIsX fx, FuncIsY fy, int id, std::string strStateXorY  )
		{
			if( (this->*fx)(id) || (this->*fy)(id) )
			{
				std::cout << "In state " << strStateXorY <<std::endl;
			}
			else
			{
				std::cout << "Not In state " << strStateXorY <<std::endl;
			}
		}
		
	public: 
	 
	 void Print()
	 {
	 	PrintIfXorY( &myCls::IsStateA, &myCls::IsStateB, 15, "A or B");
	 	PrintIfXorY( &myCls::IsStateB, &myCls::IsStateC, 5, "B or C");
	 }
	
};

int main()
{
	myCls obj;
	obj.Print();
	return 0;
}