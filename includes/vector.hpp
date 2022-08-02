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
	private:
		typedef _T											value_type;
		typedef _Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef vector_iterator								iterator; //
		typedef const_iterator; //
		typedef reverse_iterator; //
		typedef const_reverse_iterator; //
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

		// Member functions

		// constructor
		explicit vector(const allocator_type& alloc)
		: _Alloc(alloc), size(0), capacity(1)
		{
			// TODO vector allocator
		};
		explicit vector(size_type n, const value_type& value, const allocator_type& = allocator_type());
		template <class InputIterator>
			vector(InputIterator first, InpusIterator last, const allocator_type& = allocator_type());
		vector(const vector& v);
		// destructor
		~vector();
		// operator =
		vector&		operator=(const vector& x);

		// Iterators:
		iterator			begin();
		const_iterator		begin() const;
		iterator			end();
		const_iterator		end() const;
		iterator			rbegin();
		const_iterator		rbegin() const;
		iterator			rend();
		const_iterator		rend() const;


		// Capacity :
		size_type	size() const;
		size_type	max_size() const;
		void		resize(size_type n, value_type val = value_type());
		size_type	capacity() const;
		bool		empty() const;
		void		reserve(size_type n);

		// Element access
		reference		operator[](size_type n);
		const_reference operator[](size_type n) const;
		reference		at(size_type n);
		const_reference	at(size_type n) const;
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference	back() const;

		//	Modifiers
		template <class InputIterator>
		void	assign(InputIterator fist, InputIterator last); //range
		void	assign(size_type n, const value_type& val); //fill
		// TODO push_back, pop_back, insert, erase, swap, clear, emplace, emplace_back

		//	Allocator
		// TODO get_allocator




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