// Implementation of a Bounded Circular Buffer Queue
// based upon 1 Reader and 1 Writer
// 1. Size of queue is fixed at compile-time. 
// 2. Enqueue/Dequeu functions are not thread-safe. 
// 3. One slot in queue buffer is always empty to check for full queue
//
// More advanced Circular FIFO Queue has following features
// 1. Dynamic size
// 2. Thread-safe
// 3. Multiple readers and 1 writer
// 4. Different technique to detect if queue buffer is full

#include <iostream>
#include <string>
using namespace std;

#define MAX_QUEUE_SZ 4

template<class T>
class CircularFifo
{
    private:
    		// Read/Write pointers
            unsigned int read_ptr_;
            unsigned int write_ptr_;  
            
            // One location will always be empty which is used for checking 
            // if the queue is full 
			T data_[MAX_QUEUE_SZ+1]; 

    public: 
			CircularFifo();
			~CircularFifo();
            
            // Getters
            unsigned int getSize() const;
            bool getIsQueueEmpty() const;
            bool getIsQueueFull() const;

			// Setters
			void setMakeQueueEmpty();
			
            // Reader
            T dequeue();
            
            // Writer
            bool enqueue(const T& element);             

};

template<class T>
CircularFifo<T>::CircularFifo(): read_ptr_(0), write_ptr_(0)
{
	// Emtpty
}

template<class T>
CircularFifo<T>::~CircularFifo()
{
	this->setMakeQueueEmpty();
}

template<class T>
unsigned int CircularFifo<T>::getSize() const
{
	unsigned int sz = 0;
	
	if ( write_ptr_ >= read_ptr_ )
	{
		sz = ( write_ptr_ - read_ptr_ );	
	}
	else
	{
	 	sz = ( MAX_QUEUE_SZ + 1 -  (read_ptr_ - write_ptr_) ) ;
	}

	return sz;
}

template<class T>
bool CircularFifo<T>::getIsQueueEmpty() const
{
	return ( read_ptr_ == write_ptr_ );
}

template<class T>
bool CircularFifo<T>::getIsQueueFull() const
{
	return ( read_ptr_ == ( ( write_ptr_ + 1 ) % ( MAX_QUEUE_SZ + 1 ) ) );
}

template<class T>
void CircularFifo<T>::setMakeQueueEmpty()
{
	read_ptr_ = write_ptr_ = 0;
}

template<class T>
T CircularFifo<T>::dequeue( void )
{
	T element;
	
	// Block waiting if queue is empty
	while( getIsQueueEmpty() )
	{
		return static_cast<T>(0); // optional. should be removed for muli-threaded
	}
	
	element = data_[read_ptr_];
	read_ptr_ = ( read_ptr_ + 1 ) % ( MAX_QUEUE_SZ + 1 ); // Wrapping logic
	
	return element;
}

template<class T>
bool CircularFifo<T>::enqueue( const T& element )
{
	// Block waiting if queue is full
	while( getIsQueueFull() )
	{
		return false; // optional. should be removed for muli-threaded
	}
	
	data_[write_ptr_] = element;
	write_ptr_ = ( write_ptr_ + 1 ) % ( MAX_QUEUE_SZ + 1 ); // Wrapping logic
	
	return true;
}

int main() 
{
	CircularFifo<unsigned int> uiQueue;
	cout<<"Is Queue empty: "<<uiQueue.getIsQueueEmpty()<<endl;
	cout<<"Is Queue full: "<<uiQueue.getIsQueueFull()<<endl;
	
	cout<<"Enqueuing..."<<endl;
	for(unsigned int i = 10; i < 16; i++ )
	{
		cout<<"i: "<<i<<"\t";
		cout<<"Is Queue full: "<<uiQueue.getIsQueueFull()<<endl;
		uiQueue.enqueue( i );
	}
	
	cout<<"Dequeuing..."<<endl;
	for(unsigned int i = 10; i < 16; i++ )
	{
		cout<<"i: "<<i<<"\t"<<uiQueue.dequeue()<<"\t";
		cout<<"Is Queue empty: "<<uiQueue.getIsQueueEmpty()<<endl;
	}
	
	for(unsigned int i = 10; i < 12; i++ )
	{
		cout<<"i: "<<i<<"\t";
		cout<<"Is Queue full: "<<uiQueue.getIsQueueFull()<<endl;
		uiQueue.enqueue( i );
	}
	
	cout<<"Dequeuing..."<<endl;
	for(unsigned int i = 10; i < 16; i++ )
	{
		cout<<"i: "<<i<<"\t"<<uiQueue.dequeue()<<"\t";
		cout<<"Is Queue empty: "<<uiQueue.getIsQueueEmpty()<<endl;
	}
	
	return 0;
}