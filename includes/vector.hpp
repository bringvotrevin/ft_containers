#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <iterator>

namespace ft {

template <class T, class Alloc = std::allocator<T> > 
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
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

		allocator_type	_alloc;
		// ex) std::allocator<int> _alloc;
		pointer			_p;
		size_type		_size;
		size_type		_capacity;

		// Member functions
	public:
		// constructor
		explicit vector(const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _p(0), _size(0), _capacity(1)
		{
			// TODO check max size & throw
			// 최소 capacity를 0이 아닌 1로 만들면 예외처리가 더 편함 -by jwk
			_p = _alloc.allocate(_capacity);
		}
		explicit vector(size_type n, const value_type& value, const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _p(0), _size(n), _capacity() // REVIEW capacity?
		{
			// TODO check max size & throw
			// TODO allocate and construct
		}
		// TODO
		template <class InputIterator>
		vector(InputIterator first, InpusIterator last, const allocator_type& = allocator_type())
		{

		}
		vector(const vector& v)
		{

		}
		// TODO destructor
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
			return (reverse_iterator(end()));
		}
		const_iterator	rbegin() const
		{
			return (const_reverse_iterator(end()));
		}
		iterator		rend()
		{
			return (reverse_iterator(begin()));
		}
		const_iterator	rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		// Capacity :
		size_type	size() const
		{
			return (_size);
		}
		size_type	max_size() const // REVIEW check
		{
			return (std::numeric_limits<T>::max());
		}
		void		resize(size_type n, value_type val = value_type()) // REVIEW check
		{
			if (n > max_size())
				throw (std::length_error("ERROR: in resize"));
			if (_size > n)
			{
				if (_capacity > n)
				{
					for (size_t i = _size; i < n; i++)
						_alloc.destroy(&_p[i]);
					_size = n;
				}
				else
				{
					ft::vector<value_type> new_v(n, val);
					_alloc.deallocate(begin(), end());
					_alloc.destroy(_p);
					*this = new_v;
				}
			}
			else
			{
				_size = n;
				_alloc.destory(iterator(_p[_size]), end());
			}
		}
		size_type	capacity() const
		{
			return (_capacity);
		}
		bool		empty() const
		{
			return (_size == 0);
		}
		void		reserve(size_type n) // REVIEW check
		{
			if (n > max_size())
				throw (std::length_error("ERROR: in reserve"));
			if (_capacity < n)
			{
				value_type new_alloc;
				new_alloc._alloc.allocate(n);
				for (ft::vector<new_alloc.value_type>::iterator new_it = new_alloc.begin(),
						ft::vector<value_type>::iterator it = begin(); it != end(); new_it++, it++)
					{
						new_alloc._alloc.construct(new_it, *it);
						_alloc.destroy(&(*it));
					}
				_alloc.deallocate(_p, _capacity);
				*this = new_alloc;
			}
		}
		// Element access // TODO
		reference		operator[](size_type n);
		const_reference operator[](size_type n) const;
		reference		at(size_type n)
		{
			// REVIEW exception?
			return (_p[n]);
		}
		const_reference	at(size_type n) const
		{
			return (_p[n]);
		}
		reference		front()
		{
			// Unlike member vector::begin, 
			// which returns an iterator to this same element,
			// this function returns a direct reference.
			return (_p[0]);
		}
		const_reference	front() const
		{
			return (_p[0]);
		}
		reference		back()
		{
			return (_p[_size - 1]);
		}
		const_reference	back() const
		{
			return (_p[_size - 1]);
		}
		//	Modifiers
		void		assign(size_type n, const value_type& val) // TODO after clear, push_back
		{
			// fill : the new contents are n elements, each initialized to a copy of val.
			if (n <= _capacity)
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&(_p[i]));
				for (i = 0; i < n; i++)
					_alloc.construct(&(_p[i]), val);
				_size = n;
			}
			else
			{
				pointer	new_p = _alloc.allocate(n);

				for (int i = 0; i < n; i++)
					new_p[i] = val;
				pointer tmp = _p;
				while (*tmp)
					_alloc.destroy(tmp++);
				_alloc.deallocate(_p, _size);
				_p = new_p;
			}
		}
		template <class InputIterator>
		void		assign(InputIterator fist, InputIterator last) // TODO after clear, push_back
		{
			// range : the new contents are elements constructed from each of the elements
			//		in the range between first and last, in the same order.
			
		}
		void		push_back(const value_type& val)
		{
			
		}
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