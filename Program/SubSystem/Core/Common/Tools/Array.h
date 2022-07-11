/**
* @file  Array.h
* @brief array�z��𑽎����z��ɑΉ������邽�߂Ɋg��
*
* @date	 2022/07/12 2022�N�x����
*/
#pragma once


#include <array>

template<typename T, std::size_t size, std::size_t... sizes>
struct _Array
{
	using type = std::array<typename _Array<T, sizes...>::type, size>;
};

template<typename T, std::size_t size>
struct _Array<T, size>
{
	using type = std::array<T, size>;
};

template<class T, size_t size, size_t... sizes>
using Array = typename _Array<T, size, sizes...>::type;