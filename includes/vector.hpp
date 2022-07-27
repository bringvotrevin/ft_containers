#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
#include <memory>

namespace ft {

template <class _T, class _Alloc = std::allocator<_T> >
class  vector
{
    public:
        /*
        vector(); //allocator로 생성?
        vector&    operator=(const vector& other)
        {
            if (this != other)
                *this = other;
            return (*this);
        };
        ~vector();
        */

       using value_type = _T;
       using allocator_type = _Alloc;
       using reference = _T&;
       using const_reference = const T&;
       using pointer = _T*; // ??;
       using const_pointer = const _T*;
       using iterator = ;





};

//ms 24 const vector iterator
template <class _V>
class _V_const_iterator // iterator_base 상속받음
{

};

template <class _V>
class _V_iterator // const v itorator 상속받음
{

};









}





// enable_if
template <bool B, class T = void>
struct enable_if{};

template<class T>
struct enable_if<true, T> {typedef T type;};

#endif