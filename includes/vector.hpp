#ifndef VECTOR_H
#define VECTOR_H

#include "vector_iterator.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <iterator>

namespace ft {

template <class T, class Alloc = std::allocator<_T> >
class  vector
{
	private:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef ft::vector_iterator<pointer>				iterator;
		typedef ft::vector_iterator<const_pointer>			const_iterator;
		typedef reverse_iterator; // TODO reverse iterator
		typedef const_reverse_iterator; // 
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

		// REVIEW ask jwkim
		allocator_type	_alloc;
		pointer			_p; // REVIEW allocator_type::pointer인데 _p[]로 활용?
		size_type		_size;
		size_type		_capacity;

		// Member functions
	public:
		// constructor
		explicit vector(const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _p(0), _size(0), _capacity(1)
		{
			// TODO check max size & throw
			_p = _alloc.allocate(capacity);
		}
		explicit vector(size_type n, const value_type& value, const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _p(0), _size(n), _capacity() // REVIEW capacity?
		{
			// TODO check max size & throw
			// TODO allocate and construct
		}
		template <class InputIterator>
		vector(InputIterator first, InpusIterator last, const allocator_type& = allocator_type())
		{

		}
		vector(const vector& v)
		{

		}
		// destructor
		~vector();
		
		// operator =
		vector&		operator=(const vector& x);

		// Iterators:
		iterator		begin()
		{
			return (iterator(&_p[0]));
		}
		const_iterator	begin() const
		{
			return (const_iterator(&_p[0]));
		}
		iterator		end()
		{
			return (iterator(&_p[_size]));
		}
		const_iterator	end() const
		{
			return (const_iterator(&_p[_size]));
		}
		iterator		rbegin()
		{
			return (iterator(&p[_size - 1]));
		}
		const_iterator	rbegin() const
		{
			return (const_iterator(&p[_size - 1]));
		}
		iterator		rend(); // TODO add rend
		const_iterator	rend() const;


		// Capacity :
		size_type	size() const
		{
			return (_size);
		}
		size_type	max_size() const;
		void		resize(size_type n, value_type val = value_type());
		size_type	capacity() const
		{
			return (_capacity);
		}
		bool		empty() const
		{
			return (_size == 0);
		}
		void		reserve(size_type n);

		// Element access
		reference		operator[](size_type n);
		const_reference operator[](size_type n) const;
		reference		at(size_type n)
		{
			// REVIEW exception?
			return (_p[n]);
		}
		const_reference	at(size_type n) const;
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference	back() const;

		//	Modifiers
		template <class InputIterator>
		void		assign(InputIterator fist, InputIterator last); //range
		void		assign(size_type n, const value_type& val); //fill
		void		push_back(const value_type& val);
		void		pop_back();
		iterator	insert(iterator position, const value_type& val); //single element
		void		insert(iterator position, size_type n, const value_type& val); //fill
		template <class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last); //range
		iterator	erase(iterator position);
		iterator	erase(iterator fist, iterator lase);
		void		swap(vector& x);
		void		clear();
		template <class... Args>
		iterator	emplace(const_iterator position, Args&&... args);
		template <class... Args>
		iterator	emplace_back(Args&&... args);

		//	Allocator
		allocator_type	get_allocator() const;




};



}






// enable_if
template <bool B, class T = void>
struct enable_if{};

template<class T>
struct enable_if<true, T> {typedef T type;};

#endif