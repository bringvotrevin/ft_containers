#ifndef INABLE_IF
#define INABLE_IF

#include <iostream>

namespace ft{

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T>
{
	typedef T type;
};

}

#endif