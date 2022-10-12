#ifndef	ITERATOR_HPP
#define ITERATOR_HPP

#include <iostream>
#include <iterator>
#include <cstddef> // ptrdiff_t?

namespace ft {

template <class Iterator>
class vector_iterator : public ft::iterator_traits<Iterator> // REVIEW	iterator<Iterator>
{
	typedef typename vector_iterator::iterator_category		iterator_category;
	typedef typename vector_iterator::value_type			value_type;
	typedef typename vector_iterator::difference_type		difference_type;
	typedef typename vector_iterator::pointer				pointer;
	typedef typename vector_iterator::reference				reference;
};

template <class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
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
		iterator_type		_it_ty;
	public:
	// member functions
		reverse_iterator() : _it_ty {}
		explicit reverse_iterator(iterator_type it) : _it_ty(it) {}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it)
		: _it_ty(rev_it._it_ty) {}

		iterator_type	base() const
		{
			return (_it_ty);
		}
		reference			operator*() const
		{
			iterator_type	tmp = _it_ty;
			tmp--;
			return (*tmp);
		}
		reverse_iterator	operator+(difference_type n) const
		{
			reverse_iterator	tmp(_it_ty - n);
			return (tmp);
		}
		reverse_iterator&	operator++()
		{
			_it_ty--;
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
			reverse_iterator	tmp(_it_ty + n);
			return (tmp);
		}
		reverse_iterator&	operator--()
		{
			_it_ty++;
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
			return (&(_it_ty[-n - 1])); // REVIEW 맞는 코드인지 체크
		}

};

template <class It1, class It2>
bool operator==(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return ();
}

template <class It1, class It2>
bool operator!=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{

}

template <class It1, class It2>
bool operator<(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{

}

template <class It1, class It2>
bool operator<=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{

}

template <class It1, class It2>
bool operator>(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{

}

template <class It1, class It2>
bool operator>=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{

}


}

#endif