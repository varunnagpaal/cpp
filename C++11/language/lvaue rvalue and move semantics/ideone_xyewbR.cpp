// Rvalue references and Move semantics
#include <iostream>
using namespace std;

template<typename T>
class MyVector
{
	private:
		T *elements_;
		size_t size_;
	
	public:
	
		// Default Constructor
		MyVector(): elements_(nullptr), size_(0)
		{
			
		}
		
		// Constructor to Initialize Vector with given count of elements
		MyVector( size_t _size ): elements_(new T[_size]), size_(_size)
		{
			
		}
		
		~MyVector()
		{
			delete[] elements_;
			elements_ = nullptr;
		}
		
		// Copy constructor
		MyVector(MyVector const &vector): elements_(new T[vector.size()]), size_(vector.size())
		{
			// Copy elements
			for( auto i = 0; i != vector.size() ; ++i )
			{
				elements_[i] = vector[i];
			}
		}
		
		// Copy assignment operator
		MyVector & operator=(MyVector const &vector)
		{
			if( this != &vector )
			{
				T* tempElements = new T[vector.size()];
				for( auto i = 0; i != vector.size() ; ++i )
				{
					tempElements[i] = vector[i];
				}
				
				delete[] elements_;
				elements_ = tempElements;
				size_ = vector.size();
			}
			return *this;
		}
		
		// Move constructor
		MyVector( MyVector && vector): elements_(vector.elements_), size_(vector.size_)
		{
			vector.elements_ = nullptr;
			vector.size_ = 0;
		}
		
		// Move assignment 
		MyVector && operator=(MyVector && vector)
		{
			if( this != &vector )
			{
				delete[] elements_;
				
				elements_ = vector.elements_;
				size_ = vector.size_;
				
				vector.elements_ = nullptr;
				vector.size_ = 0;
				
			}
			
			return *this;
		}

		T& operator[]( size_t index )
		{
			return elements_[index]; 
		}
		
		T const& operator[]( size_t index ) const
		{
			return elements_[index];
		}
		
		size_t size() const{ return size_;}
		
		MyVector operator+( MyVector const & vector) const
		{
			assert( this->size() == vector.size() );
			
			MyVector temp( this->size() );
			for( auto i =0 ; i!= this->size() ; ++i)
			{
				temp[i] = this->elements_[i] + vector[i];
			}
			
			return temp;
		}
		
};
	

int main() {
	// your code goes here
	return 0;
}