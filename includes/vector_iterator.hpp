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


}

#endif