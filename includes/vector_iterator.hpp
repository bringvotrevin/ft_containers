#ifndef	VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iostream>
#include <iterator>
#include <cstddef> // ptrdiff_t?

namespace ft {

template <class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
class vector_iterator : public ft::iterator_traits<Iterator> // REVIEW	iterator<Iterator>
{
	public :
		//TODO vector_iterator
		typedef typename Category		iterator_category;
		typedef typename T				value_type;
		typedef typename Distance		difference_type;
		typedef typename Pointer		pointer;
		typedef typename Reference		reference;

		iterator_category random_access_iterator_tag;
		
};

}

template <class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
class iterator
{
	public :
		typedef typename Category		iterator_category;
		typedef typename T				value_type;
		typedef typename Distance		difference_type;
		typedef typename Pointer		pointer;
		typedef typename Reference		reference;
};

template <class Iterator>
class iterator_traits
{
	public :
		typedef typename Iterator::diffrence_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;

};

#endif