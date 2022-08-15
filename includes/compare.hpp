#ifndef COMPARE_HPP
#define COMPARE_HPP

#include "iterator.hpp"
#include <iostream>

namespace ft{

template <class InputIt1, class InputIt2>
bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
	for (; first1 != last1; first1++, first2++)
	{
		if (first1 != first2)
			return (false);
	}
	return (true);
};

template <class InputIt1, class InputIt2, class BinaryPredicate>
bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
{
	for (; first1 != last1; first1++; first2++)
	{
		if (!p(*first1, *first2))
			return (false);
	}
	return (true);
};

template <class InputIt1, class InputIt2>
bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2)
{
	// 첫번째 반복자가 두번째 반복자보다 사전순으로 작으면 true 반환
	// 두개의 이터레이터 비교해서 더 긴 길이 기준으로 반복문 돌림
	// 현재 반복자 위치의 값 크기 비교하며 반복자 한 칸씩 증가
	// 중간에 last가 먼저 나오거나 더 작은 원소를 가지고 있는 반복자가 더 작은 값이 됨
	// 빈 원소나 둘 다 같은 경우는 equal

	// operator< 로 비교
	for (; (first1 != last1) && (first2 != last2); first1++, first2)
	{
		if (*first1 < *first2)
			return (true);
		else if (*first1 > *first2)
			return (false);
	}
	if ((first1 == last1) && (fist2 != last2))
		return (true);
	else
		retur (false);
};

template <class InputIt1, class InputIt2, class Compare>
bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2, Compare comp)
{
	// comp이용해서 비교
	for (; (first1 != last1) && (first2 != last2); first1++, first2)
	{
		if (comp(*fisrt1, *first2))
			return (true);
		else
			return (false);
	}
	if ((first1 == last1) && (fist2 != last2))
		return (true);
	else
		retur (false);
};

}

#endif