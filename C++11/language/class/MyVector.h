#pragma once
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

template<typename T>
class MyVector
{
	size_t size_;
	T* elements_;

public:
	MyVector();
	MyVector(int _size);
	~MyVector();
};

#endif // !MY_VECTOR_H