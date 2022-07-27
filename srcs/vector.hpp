#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>

namespace ft {

template <class T, class Alloc = allocator<T> >
class  vector
{
    public:
        vector(); //allocator로 생성?
        vector&    operator=(const vector& other)
        {
            if (this != other)
                *this = other;
            return (*this);
        };
        ~vector();

};









}





// enable_if
template <bool B, class T = void>
struct enable_if{};

template<class T>
struct enable_if<true, T> {typedef T type;};