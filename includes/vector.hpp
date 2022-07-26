#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "iterator.hpp"
#include "util.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <iterator>

namespace ft {

template <class T, class Alloc = std::allocator<T> > 
class  vector
{
	private:
		typedef Alloc										 allocator_type;
	public:
		typedef T											value_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		// ex) std::allocator<int>::pointer
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef ft::vector_iterator<pointer>				iterator;
		// ex) vector_iterator<std::allocator<int>::pointer>
		typedef ft::vector_iterator<const_pointer>			const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
	private:
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
			// REVIEW check max size & throw
			// if (_capacity > max_size())
			// 	throw (std::bad_alloc()); =>  과연 필요한가?

			// 최소 capacity를 0이 아닌 1로 만들면 예외처리가 더 편함 -by jwk
			_p = _alloc.allocate(_capacity);
		}
		explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _p(0), _size(n), _capacity(n)
		{
			_p = _alloc.allocate(_capacity);
			for (size_type i = n; i > 0; i--)
				_alloc.construct(&(_p[i]), value);
		}
		// TODO
		template <class InputIterator>
		vector(typename ft::enable_if<!(ft::is_integral<InputIterator>::value), InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _p(0), _size(0), _capacity(0)
		{
			// if (ft::is_integral<InputIterator>::value) // 위에서 걸러주고 지우기
			// {
			// 	_alloc = alloc;
			// 	_size = first;
			// 	_capacity = first;
			// 	_p = _alloc.allocate(_capacity);
			// 	for (size_type i = first; i > 0 ; i--)
			// 		_alloc.construct(&(_p[i]), last);
			// 	return;
			// }
			if (ft::is_same<typename ft::iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag>::value) // TODO inputiterator case
			{
				_p = _alloc.allocate(1);
				_capacity = 1;
				for (; first != last; first++)
					push_back(*first);
			}
			else
			{
				size_type n = ft::distance(first, last);
				_p = _alloc.allocate(n);
				_capacity = n;
				for (size_type i = 0; first != last; i++, first++)
					_alloc.construct(&(_p[i]), *first);
				_size = n;
			}
		}
		vector(const vector& v)
		: _alloc(v._alloc), _size(v._size), _capacity(v._capacity)
		{
			_p = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&(_p[i]), v._p[i]);
		}
		~vector()
		{
			clear();
			_alloc.deallocate(_p, _capacity);
			_p = NULL;
			_size = 0;
			_capacity = 0;
		};
		
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

		// REVIEW check jw's [why not?]
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
					_alloc.destroy(&(_p[i]));
				}
				_alloc.deallocate(_p, _capacity);
				_p = new_p;
				_capacity = n;
			}
		}

		reference		operator[](size_type n)
		{
			return (_p[n]);
		};
		const_reference operator[](size_type n) const
		{
			return (_p[n]);
		};

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
		void		assign(size_type n, const value_type& val)
		{
			// fill : the new contents are n elements, each initialized to a copy of val.
			if (n <= _capacity)
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&(_p[i]));
				for (size_t i = 0; i < n; i++)
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
				_alloc.deallocate(_p, _capacity);
				_p = new_p;
			}
		}
		template <class InputIterator>
		void		assign(typename ft::enable_if<ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) // TODO after clear, push_back
		{
			// range : the new contents are elements constructed from each of the elements
			//		in the range between first and last, in the same order.
			if (ft::is_same<typename ft::iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag>::value) // TODO case of inputitertaor
			{
				clear();
				for (; first != last; first++)
					push_back(*first);
			}
			else
			{
				size_type n = ft::distance(first, last);
				if (n > _capacity)
				{
					size_type tmp_size = _size;
					clear();
					pointer tmp_p = _alloc.allocate(n);
					for(size_type i = 0; first != last; i++, first++)
						_alloc.construct(&(tmp_p[i]), *first);
					_alloc.deallocate(_p, _capacity);
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
				reserve(_size * 2);
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
			size_type pos = end() - position;
			if (_capacity < _size + 1)
				reserve(_size * 2);
			iterator end = end(), cur = end - 1;
			_alloc.constuct(&end, *cur);
			end--;
			cur--;
			for (--pos; pos > 0; end--, cur--, pos--)
				*end = *cur;
			*end = val;
			_size += 1;
			return (end);
		}
		void		insert(iterator position, size_type n, const value_type& val) //fill
		{
			size_type pos = end() - position;
			if (_capacity < _size + n)
			{
				if (_size * 2 < n)
					reserve(n);
				else
					reserve(_size * 2);
			}
			iterator re_end = end() - 1;
			iterator copy_end = re_end - n;
			size_type new_alloc = n, num = n;
			for (; pos > 0; pos--, re_end--, copy_end--)
			{
				if (new_alloc > 0)
				{
					_alloc.construct(&re_end, *copy_end);
					new_alloc--;
				}
				else
				{
					*re_end = *copy_end;
					n--;
				}
			}
			for (; new_alloc > 0; re_end--, new_alloc--, num--)
				_alloc.construct(&re_end--, val);
			for (; num > 0; num--)
				*re_end = val;
			_size += n;
		}
		template <class InputIterator>
		void		insert(iterator position, typename ft::enable_if<ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) //range
		{
			if (ft::is_same<typename ft::iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag>::value) // TODO case of inputiterator
			{
				vector new_v;
				iterator it = begin();
				for (; it != position; it++)
					new_v.push_back(*it);
				for (; first != last; first++)
					new_v.push_back(*first);
				for (; it != end(); it++)
					new_v.push_back(*it);
				for (int i = 0; i < _size; i++)
					_alloc.destroy(&(_p[i]));
				_alloc.deallocate(_p, _capacity);
				*this = new_v;
				return ;
			}
			else
			{
				difference_type	dist = ft::distance(first, last);
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
				_alloc.deallocate(_p, _capacity);
				*this = new_v;
			}
		}
		iterator	erase(iterator position)
		{
			if (position + 1 != end())
			{
				for (iterator pos = position, cur = position + 1; cur != end(); cur++, position++)
					*pos = *cur;
			}
			_alloc.destroy(end() - 1);
			_size--;
			return (position);
		}
		iterator	erase(iterator first, iterator last)
		{
			size_type	n = ft::distance(first, last);
			iterator	start = first;
			if (first != last)
			{
				if (last != end())
				{
					size_type cnt = 0;
					for (size_type i = 0; i < n; i++, start++)
					{
						_alloc.destroy(start);
						if (++last != end())
						{
							_alloc.construct(start, *last);
							cnt++;
						}
					}
					_size -= n;
					return (first + 1 + cnt);
				}
				else
				{
					iterator start = first;
					for (; start != last; start++)
						_alloc.destroy(start);
					_size -= n;
					return (first + 1);
				}
			}
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

#endif