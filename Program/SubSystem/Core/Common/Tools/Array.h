/**
* @file  Array.h
* @brief array配列を多次元配列に対応させるために拡張
*
* @date	 2022/07/12 2022年度初版
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