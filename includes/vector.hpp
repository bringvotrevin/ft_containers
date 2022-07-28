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
      typedef _T                                         value_type;
      typedef _Alloc                                     allocator_type;
      typedef typename allocator_type::reference         reference;
      typedef typename allocator_type::const_reference   const_reference;
      typedef typename allocator_type::pointer           pointer;
      typedef typename allocator_type::const_pointer     cons_pointer;

      typedef iterator; //
      typedef const_iterator; //
      typedef reverse_iterator; //
      typedef const_reverse_iterator; //
      typedef difference_type; //
      typedef size_type; //




      //  using value_type = _T;
      //  using allocator_type = _Alloc;
      //  using reference = _T&;
      //  using reference = allocator_type::reference;
      //   using const_reference = const T&;
      //  using const_reference = allocator_type::const_reference;
      //   using pointer = _T*; // ??;
      //  using pointer = allocator_type::pointer;
      //   using const_pointer = const _T*;
      //  using const_pointer = allocator_type::const_pointer;

      //  using iterator = ;
      //  using const_iterator = ;
      //  using reverse_iterator = ;
      //  using const_reverse_iterator = ;

      //  using difference_type = ;
      //  using size_type = ;





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