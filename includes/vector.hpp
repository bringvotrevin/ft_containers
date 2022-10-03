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

		std::vector<int>::allocator<int>::pointer::
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
		explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _p(0), _size(n), _capacity(n) // REVIEW capacity?
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
		vector&		operator=(const vector& x)
		{
			if (_capacity < x._size)
				reserve(x._size);
			clear();
			assign(x.begin(), x.end());
			_size = x._size;
			return (*this);
		}

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

		// REVIEW check
		size_type	max_size() const
		{
			return (std::numeric_limits<T>::max());
		}

		void		resize(size_type n, value_type val = value_type()) // REVIEW check
		{
			size_type i;
			if (n < _capacity)
			{
				if (n < _size)
				{
					for (i = n; n < _size; n++)
 	 	 				_alloc.destroy(&(_p[i]));
					_size = n;
				}
				else
				{
					for (i = _size; i < n; i++)
						_alloc.construct(&(_p[i]), val);
					_size = n;
				}
			}
			else
			{
				reserve(n);
				for (i = _size; i < n; i++)
					_alloc.construct(&(_p[i]), val);
				_size = n;
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
				pointer new_p = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(&(new_p[i]), _p[i]);
					_alloc.destroy(_p[i]);
				}
				_alloc.deallocate(_p, _capacity);
				_p = new_p;
				_capacity = n;
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
		void		assign(InputIterator first, InputIterator last) // TODO after clear, push_back
		{
			// range : the new contents are elements constructed from each of the elements
			//		in the range between first and last, in the same order.
			if () // case of inputitertaor
			{
				clear();
				for (; first != last; first++)
					push_back(*first);
			}
			else
			{
				size_type n = std::distance(first, last);
				if (n > _capacity)
				{
					size_type tmp_size = _size;
					clear();
					pointer tmp_p = _alloc.allocate(n);
					for(size_type i = 0; first != last; i++, first++)
						_alloc.construct(&(tmp_p[i]), *first);
					_alloc.deallocate(_p, tmp_size);
					_p = tmp_p;
					_size = n;
					_capacity = n;
				}
				else if (_size > n)
				{
					erase(_p[n], end());
					for (size_type i = 0; first != last; i++, first++)
					{
						_alloc.destroy(_p[i]);
						_alloc.construct(&(_p[i]), *first);
					}
				}
				else
				{
					clear();
					for (size_type i = 0; first != last; i++, first++)
						_alloc.construct(&(_p[i]), *first);
					_size = n;
				}
			}
		}
		void		push_back(const value_type& val)
		{
			if (_capacity < _size + 1)
				reserve(size * 2);
			_alloc.construct(end(), val);
			_size++;
		} 
		void		pop_back()
		{
			if (_size < 1)
				return ;
			erase(--end());
			_size--;
		}
		iterator	insert(iterator position, const value_type& val) //single element
		{
			if (_capacity < _size + 1)
				reserve(_size * 2);
			iterator end = end(), cur = end - 1;
			_alloc.constuct(&end, *cur);
			end--;
			cur--;
			for (; cur != position; end--, cur--)
				*end = *cur;
			*position = val;
			_size += 1;
			return (position);
		}
		void		insert(iterator position, size_type n, const value_type& val) //fill
		{
			if (_capacity < _size + n)
			{
				if (_size * 2 < n)
					reserve(n);
				else
					reserve(_size * 2);
			}
			iterator end = end() + (n - 1);
			for (iterator cur = end - 1; cur != end() - 1; end--, cur--)
			{
				if (cur < )
				_alloc.construct(&end, *cur);

			}
			for (; cur != position + (n - 1); end--, cur--)
				*end = *cur;
			_size += n;
		}
		template <class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last) //range
		{
			// the new capacity cannot determined beforehand
			// 1) using push_back?
			// iterator cp_pos = position;
			// iterator ori_begin = begin();
			// if (_capacity < _size + n)
			// {
			// 	if (_size * 2 < n)
			// 		reserve(n);
			// 	else
			// 		reserve(_size * 2);
			// 	// reserve 후 기존 벡터 참조 가능??
			// }
			// // inputiterator 범위 복사
			// int i = 0;
			// for (iterator it = ori_begin; it != cp_pos; it++, i++)
			// 	_p[i] = *it;
			// for (; first != last, i < mmmmmmmm.....; first++, i++)
			// 	_p[i];
			// TODO .....dk

			// 2nd try
			if () // case of inputiterator
			{
				vector new_v;
				iterator it = begin();
				for (; it != position; it++)
					new_v.push_back(*it);
				for (; first != last; first++)
					new_v.push_back(*first);
				for (; it != end(); it++)
					new_b.push_back(*it);
				for (int i = 0; i < _size; i++)
					_alloc.destroy(&(_p[i]));
				_alloc.deallocate(_p, _size);
				*this = new_v;
				return ;
			}
			else // other iterator
			{
				difference_type	dist = distance(first, last);
				vector 			new_v(_size + dist);
				iterator		tmp = begin();
				int				i = 0;

				for (; tmp != position; i++, tmp++)
					new_v._alloc.construct(&(new_v._p[i]), *tmp);
				for (; first != last; i++, first++)
					new_v._alloc.construct(&(new_v._p[i]), *first);
				for (; tmp != end(); i++, tmp++)
					new_v._alloc.construct(&(new_v._p[i]), *tmp);
				for (i = 0; i < _size; i++)
					_alloc.destroy(&(_p[i]));
				_alloc.deallocate(_p, _size);
				*this = new_v;
			}
		}
		iterator	erase(iterator position)
		{
			if (position != --end())
			{
				iterator cur = position;
				_alloc.destroy(position++);
				for (; position != end(); cur++, position++)
				{
					_alloc.construct(cur, *position);
					_alloc.destroy(position);
				}
				_alloc.destroy(cur);
				_size--;
			}
			else
			{
				_alloc.destroy(position);
				_size--;
			}
		}
		iterator	erase(iterator first, iterator last)
		{
			size_type n = std::distance(first, last);
			// first시작범위부터 destroy하며 n개 뒤 원소가 할당된것일경우 복사

		}
		void		swap(vector& x)
		{
			pointer	tmp = _p;
			_p = x._p;
			x._p = tmp;

			size_type	tmp_size = _size;
			_size = x._size;
			x.size = tmp_size;

			size_type tmp_capacity = _capacity;
			_capacity = x._capacity;
			x._capacity = tmp_capacity;

			allocator_type tmp_alloc = _alloc;
			_alloc = x.get_allocator();
			x.alloc = tmp_alloc;
		}
		void		clear()
		{
			for (iterator it = begin(); it != end(); it++)
				erase(it);
			_size = 0;
		}

		//	Allocator
		allocator_type	get_allocator() const
		{
			return (_alloc);
		}
};


}






// enable_if
template <bool B, class T = void>
struct enable_if{};

template<class T>
struct enable_if<true, T> {typedef T type;};

#endif