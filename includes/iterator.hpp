#ifndef	ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <iterator>
#include <cstddef> // ptrdiff_t?
#include "util.hpp"

namespace ft {


template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator
{
	typedef Category		iterator_category;
	typedef T				value_type;
	typedef Distance		difference_type;
	typedef Pointer			pointer;
	typedef Reference		reference;
};

template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::iterator_category	iterator_category;
	typedef typename Iterator::diffrence_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
};

template <class T>
struct iterator_traits<T*>
{
	typedef std::random_access_iterator_tag		iterator_category;
	typedef ptrdiff_t							difference_type; // REVIEW ptrdiff
	typedef T									value_type;
	typedef T*									pointer;
	typedef T&									reference;
};

template <class T>
struct iterator_traits<const T*>
{
	typedef std::random_access_iterator_tag		iterator_category;
	typedef ptrdiff_t							difference_type; // REVIEW ptrdiff
	typedef T									value_type;
	typedef const T*							pointer;
	typedef const T&							reference;
};

template <class Iterator>
class vector_iterator : public ft::iterator_traits<Iterator> // REVIEW iterator<Iterator>
{
	private:
		Iterator _base;
	public: 
		typedef typename vector_iterator::iterator_category		iterator_category;
		typedef typename vector_iterator::value_type			value_type;
		typedef typename vector_iterator::difference_type		difference_type;
		typedef typename vector_iterator::pointer				pointer;
		typedef typename vector_iterator::reference				reference;

		// TODO constructor and destructor
		vector_iterator() : _base(Iterator()) {}
		explicit vector_iterator(const Iterator& other) : _base(other) {}
		template <typename o_Iterator>
		vector_iterator(const vector_iterator<o_Iterator> other, typename ft::enable_if<ft::is_same<o_Iterator, Iterator>::vaue>* = 0)
		: _base(other._base) {}


		const Iterator&		base() const
		{
			return (_base);
		}

		// REVIEW lvalue도 될 수 있게 reference 반환
		reference			operator*() const
		{
			return (*(_base));
		}

		pointer				operator->() const
		{
			return (_base);
		}

		reference			operator[](difference_type n) const
		{
			return (_base[n]);
		}

		vector_iterator&	operator=(const vector_iterator& other) 
		{
			_base = other._base;
			return (*this);
		}

		vector_iterator		operator+(difference_type n)
		{
			vector_iterator tmp = *this;
			tmp._base = tmp._base + n;
			return (tmp);
		}

		vector_iterator		operator-(difference_type n)
		{
			vector_iterator tmp = *this;
			tmp._base = tmp._base - n;
			return (tmp);
		}

		vector_iterator&	operator+=(difference_type n)
		{
			*this = *this + n;
			return (*this);
		}

		vector_iterator&	operator-=(difference_type n)
		{
			*this = *this - n;
			return (*this);
		}

		difference_type		operator-(vector_iterator other)
		{
			return (this->_base - other._base);
		}

		vector_iterator&	operator++()
		{
			_base++;
			return (*this);
		}

		vector_iterator		operator++(int)
		{
			vector_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		vector_iterator&	operator--()
		{
			_base--;
			return (*this);
		}

		vector_iterator		operator--(int)
		{
			vector_iterator tmp = *this;
			--(*this);
			return (tmp);
		}

		template <class It1, class It2>
		friend bool operator==(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs);
		template <class It1, class It2>
		friend bool operator!=(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs);
		template <class It1, class It2>
		friend bool operator<(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs);
		template <class It1, class It2>
		friend bool operator<=(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs);
		template <class It1, class It2>
		friend bool operator>(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs);
		template <class It1, class It2>
		friend bool operator>=(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs);

};

template <class It1, class It2>
bool operator==(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
{
	return (lhs._base == rhs._base);
}

template <class It1, class It2>
bool operator!=(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
{
	return (lhs._base != rhs._base);
}

template <class It1, class It2>
bool operator<(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
{
	return (lhs._base > rhs._base);
}

template <class It1, class It2>
bool operator<=(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
{
	return (lhs._base <= rhs._base);
}

template <class It1, class It2>
bool operator>(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
{
	return (lhs._base > rhs._base);
}

template <class It1, class It2>
bool operator>=(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)
{
	return (lhs._base >= rhs._base);
}





template <typename RandomAccessIterator>
typename iterator_traits<RandomAccessIterator>::difference_type
_distance(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
{
	return (last - first);
};

template <typename InputIterator>
typename iterator_traits<InputIterator>::difference_type
_distance(InputIterator first, InputIterator last, std::input_iterator_tag)
{
	typename iterator_traits<InputIterator>::diffrence_type result = 0;
	for (; first != last; first++)
		result++;
	return (result);
}

template <typename It>
typename iterator_traits<It>::difference_type
distance(It first, It last)
{
	return (_distance(first, last, typename iterator_traits<It>::iterator_category()));
}

template <class Iterator>
class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category, 
												typename ft::iterator_traits<Iterator>::value_type,
												typename ft::iterator_traits<Iterator>::difference_type,
												typename ft::iterator_traits<Iterator>::pointer,
												typename ft::iterator_traits<Iterator>::reference>
{
	private:
		typedef Iterator	iterator_type;
		iterator_type		_base;
	public:
		typedef typename reverse_iterator::difference_type difference_type;
		typedef typename reverse_iterator::pointer pointer;
		typedef typename reverse_iterator::reference reference;

	// member functions
		reverse_iterator() : _base() {}
		explicit reverse_iterator(iterator_type it) : _base(it) {}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it)
		: _base(rev_it._base()) {}

		iterator_type	base() const
		{
			return (_base);
		}
		reference	operator*() const
		{
			iterator_type	tmp = _base;
			tmp--;
			return (*tmp);
		}
		reverse_iterator	operator+(difference_type n) const
		{
			reverse_iterator	tmp(_base - n);
			return (tmp);
		}
		reverse_iterator&	operator++()
		{
			_base--;
			return (*this);
		}
		reverse_iterator	operator++(int)
		{
			reverse_iterator	tmp = *this;
			++(*this);
			return (tmp);
		}
		reverse_iterator&	operator+=(difference_type n)
		{
			*this = *this + n;
			return (*this);
		}
		reverse_iterator	operator-(difference_type n) const
		{
			reverse_iterator	tmp(_base + n);
			return (tmp);
		}
		reverse_iterator&	operator--()
		{
			_base++;
			return (*this);
		}
		reverse_iterator	operator--(int)
		{
			reverse_iterator	tmp = *this;
			--(*this);
			return (tmp);
		}
		reverse_iterator&	operator-=(difference_type n)
		{
			*this = *this - n;
			return (*this);
		}
		pointer				operator->() const // REVIEW check &&
		{
			return (&(operator*()));
		}
		reference			operator[](difference_type n) const
		{
			return (*(_base[-n - 1])); // REVIEW 맞는 코드인지 체크
		}

		template <class It1, class It2>
		friend bool operator==(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs);
		template <class It1, class It2>
		friend bool operator!=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs);
		template <class It1, class It2>
		friend bool operator<(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs);
		template <class It1, class It2>
		friend bool operator<=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs);
		template <class It1, class It2>
		friend bool operator>(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs);
		template <class It1, class It2>
		friend bool operator>=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs);
		template <class Iter>
		friend reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it);
		template <class Iter>
		friend typename reverse_iterator<Iter>::difference_type operator-(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);

};

template <class It1, class It2>
bool operator==(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return (lhs._base == rhs._base);
}

template <class It1, class It2>
bool operator!=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return (lhs._base != rhs._base);
}

template <class It1, class It2>
bool operator<(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return (lhs._base > rhs._base);
}

template <class It1, class It2>
bool operator<=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return (lhs._base >= rhs._base);
}

template <class It1, class It2>
bool operator>(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return (lhs._base < rhs._base);
}

template <class It1, class It2>
bool operator>=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return (lhs._base <= rhs._base);
}

template <class Iter>
reverse_iterator<Iter> 
operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
{
	return (it._base + n);
}

template <class Iter>
typename reverse_iterator<Iter>::difference_type 
operator-(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
{
	return (rhs._base() - lhs._base());
}

}

#endif