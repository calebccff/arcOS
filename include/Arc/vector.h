#pragma once

#include <Arc/stdint.h>

template<typename T> class Vector {
private:
	T *data;
	size_t size;
	size_t capacity;

public:

Vector<T>() : data(nullptr), size(0), capacity(0) {}

Vector<T>(size_t capacity) : data(new T[capacity]), size(0), capacity(capacity) {}

};
