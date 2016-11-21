#include <cstdint>
#include <cassert>

template<class T, std::size_t N = 32>
class MyStack
{
private:
    T _buffer[N];
    std::size_t _top;

public:

    typedef typename std::size_t size_type;     
    MyStack();    
    MyStack( MyStack const& stack );    
    MyStack const & operator=(MyStack const & stack);    
    ~MyStack();
    
    bool empty() const;    
    bool full() const;    
    size_type size() const;    
    T & top();    
    T const & top() const;    
    void push( T const & elem );    
    void pop();
};

template<class T, std::size_t N>
MyStack<T, N>::MyStack() : _top( 0 )
{
}

template<class T, std::size_t N>
MyStack<T,N>::MyStack( MyStack const& stack )
{
    this->_top = stack._top;
    for( std::size_t i = 0; i < _top;  ++i )
    {
        this->_buffer[i] = stack._buffer[i];
    }    
}

template<class T, std::size_t N>
MyStack<T, N> const & MyStack<T, N>::operator=(MyStack const & stack)
{
    if ( this != &stack )
    {
        this->_top = stack._top;
        for ( std::size_t cnt = 0; cnt < _top; ++cnt )
        {
            this->_buffer[cnt] = stack._buffer[cnt];
        }
    }
    return *this;
}

template<class T, std::size_t N>
MyStack<T,N>::~MyStack()
{
}

template<class T, std::size_t N>
bool MyStack<T,N>::empty() const
{
    return ( 0 == _top );
}

template<class T, std::size_t N>
bool MyStack<T, N>::full() const
{
    return ( _top == N );
}

template<class T, std::size_t N>
typename MyStack<T,N>::size_type MyStack<T,N>::size() const
{
    return _top;
}

// Pre: Stack should not be empty (user needs to check)
template<class T, std::size_t N>
T & MyStack<T,N>::top()
{
    assert( 0 != _top );
    return _buffer[_top - 1];
}

// Pre: Stack should not be empty (user needs to check)
template<class T, std::size_t N>
T const & MyStack<T,N>::top() const
{
    assert( 0 != _top );
    return _buffer[_top - 1];
}

// Pre: Stack should not be full (user needs to check)
template<class T, std::size_t N>
void MyStack<T,N>::push( T const & elem )
{
    assert( N != _top );
    _buffer[_top] = elem;
}

// Pre: Stack should not be empty (user needs to check)
template<class T, std::size_t N>
void MyStack<T,N>::pop()
{
    assert( 0 != _top );
    --_top;
}

int main()
{
	MyStack<int> stk;
	return 0;
}