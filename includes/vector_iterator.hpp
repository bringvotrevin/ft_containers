#ifndef	VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

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

template <class Iterator>
class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category, 
												typename ft::iterator_traits<Iterator>::value_type,
												typename ft::iterator_traits<Iterator>::difference_type,
												typename ft::iterator_traits<Iterator>::pointer,
												typename ft::iterator_traits<Iterator>::reference>
{
	private:
		typedef Iterator	iterator_type;
		iterator_type		_it;
	public:
	// member functions
		// constructor
		reverse_iterator();
		explicit reverse_iterator(iterator_type it);
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter>& rev_it);

		iterator_type	base() const
		{
			return (_it);
		}

		reference			operator*() const
		{
			iterator_type	tmp = _it;
			tmp--;
			return (*tmp);
		}
		reverse_iterator	operator+(difference_type n) const
		{
			reverse_iterator	tmp(_it - n);
			return (tmp);
		}
		reverse_iterator&	operator++()
		{
			_it--;
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
			reverse_iterator	tmp(_it + n);
			return (tmp);
		}
		reverse_iterator&	operator--()
		{
			_it++;
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
			return (&(_it[-n - 1]));
		}
};

}

#endif