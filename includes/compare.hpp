#ifndef COMPARE_HPP
#define COMPARE_HPP

#include "iterator.hpp"


namespase ft{


template <class InputIt1, class InputIt2>
bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2)
{

};

template <class InputIt1, class InputIt2, class Compare>
bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
								InputIt2 first2, InputIt2 last2, Compare comp)
{
	// 두개의 이터레이터 비교해서 더 긴 길이 기준으로 반복문 돌림
	// 현재 반복자 위치의 값 크기 비교하며 반복자 한 칸씩 증가
	// 중간에 last가 먼저 나오는 이터레이터는 더 작은 값이 됨
	
	for ()

};


}