#include <iostream>
#include <cstdint>
#include <cassert>

#define __device__

template<class T, uint8_t N = 32>
class CUStack
{
private:
    T _buffer[N];
    uint8_t _stackTop;

public:

    __device__
    CUStack();

    __device__
    CUStack( CUStack const& stack );

    __device__
    CUStack const & operator=(CUStack const & stack);

    __device__
    ~CUStack();

    __device__
    bool empty() const;

    __device__
    bool full() const;

    __device__
    uint8_t size() const;

    __device__
    T & top();

    __device__
    T const & top() const;

    __device__
    void push( T const & elem );

    __device__
    void pop();
};

template<class T, uint8_t N>
__device__
CUStack<T, N>::CUStack() : _stackTop( 0 )
{
}

template<class T, uint8_t N>
__device__
CUStack<T, N>::CUStack( CUStack const& stack )
{
    this->_stackTop = stack._stackTop;
    for ( uint8_t i = 0; i < _stackTop; ++i )
    {
        this->_buffer[i] = stack._buffer[i];
    }
}

template<class T, uint8_t N>
__device__
CUStack<T, N> const & CUStack<T, N>::operator=(CUStack const & stack)
{
    if ( this != &stack )
    {
        this->_stackTop = stack._stackTop;
        for ( uint8_t cnt = 0; cnt < _stackTop; ++cnt )
        {
            this->_buffer[cnt] = stack._buffer[cnt];
        }
    }
    return *this;
}

template<class T, uint8_t N>
__device__
CUStack<T, N>::~CUStack()
{
}

template<class T, uint8_t N>
__device__
bool CUStack<T, N>::empty() const
{
    return ( 0 == _stackTop );
}

template<class T, uint8_t N>
__device__
bool CUStack<T, N>::full() const
{
    return ( N == _stackTop );
}

template<class T, uint8_t N>
__device__
uint8_t CUStack<T, N>::size() const
{
    return _stackTop;
}

// Pre: Stack should not be empty (user needs to check)
template<class T, uint8_t N>
__device__
T & CUStack<T, N>::top()
{
    assert( 0 != _stackTop );
    return _buffer[_stackTop - 1];
}

// Pre: Stack should not be empty (user needs to check)
template<class T, uint8_t N>
__device__
T const & CUStack<T, N>::top() const
{
    assert( 0 != _stackTop );
    return _buffer[_stackTop - 1];
}

template<class T, uint8_t N>
__device__
void CUStack<T, N>::push( T const & elem )
{
    if ( !full() )
    {
        _buffer[_stackTop] = elem;
        _stackTop++;
    }
    else
    {
    	printf( "Trying to push in a full stack!!\n");
    }
}

template<class T, uint8_t N>
__device__
void CUStack<T, N>::pop()
{
    if( !empty() )
    {
        _stackTop--;
    }
    else
    {
    	printf( "Trying to pop an empty stack!!\n");
    }
}

int main() 
{
	CUStack<uint32_t,2> stack;
	
	std::cout<<"IsEmpty: " << stack.empty() << std::endl;
	std::cout<<"IsFull: " << stack.full() << std::endl;
	std::cout<<"Size: " << uint32_t(stack.size()) << std::endl;
    stack.pop();
	std::cout<<"Pushing 10: " << std::endl;
	stack.push(10);
	std::cout<<"IsEmpty: " << stack.empty() << std::endl;
	std::cout<<"IsFull: " << stack.full() << std::endl;
	std::cout<<"Size: " << uint32_t(stack.size()) << std::endl;	
	std::cout<<"Top: " << stack.top() << std::endl;
	std::cout<<"Pushing 9: " << std::endl;
	stack.push(9);
	std::cout<<"IsEmpty: " << stack.empty() << std::endl;
	std::cout<<"IsFull: " << stack.full() << std::endl;
	std::cout<<"Size: " << uint32_t(stack.size()) << std::endl;	
	std::cout<<"Top: " << stack.top() << std::endl;
	std::cout << "Popping" << std::endl;
	stack.pop();
	std::cout<<"IsEmpty: " << stack.empty() << std::endl;
	std::cout<<"IsFull: " << stack.full() << std::endl;
	std::cout<<"Size: " << uint32_t(stack.size()) << std::endl;	
	std::cout<<"Top: " << stack.top() << std::endl;
	std::cout << "Popping" << std::endl;	
	stack.pop();
	std::cout<<"IsEmpty: " << stack.empty() << std::endl;
	std::cout<<"IsFull: " << stack.full() << std::endl;
	std::cout<<"Size: " << uint32_t(stack.size()) << std::endl;
	std::cout<<"Top: " << stack.top() << std::endl;	
	
	
	return 0;
}