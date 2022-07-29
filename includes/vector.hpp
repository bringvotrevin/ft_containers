#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
#include <memory>
#include <iterator>

namespace ft {


template <class _T, class _Alloc = std::allocator<_T> >
class  vector
{
	public:
		typedef _T											value_type;
		typedef _Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		cons_pointer		
		typedef iterator; //
		typedef const_iterator; //
		typedef reverse_iterator; //
		typedef const_reverse_iterator; //
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

		explicit vector(const allocator_type&);
		explicit vector(size_type n, const value_type& value, const allocator_type& = allocator_type());
		template <class InputIterator>
			vector(InputIterator first, InpusIterator last, const allocator_type& = allocator_type());
		vector(const vector& v);

		~vector();

		vector& operator=(const vector& x);


};





}






// enable_if
template <bool B, class T = void>
struct enable_if{};

template<class T>
struct enable_if<true, T> {typedef T type;};

#endif