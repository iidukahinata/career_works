/**
* @file    D3D12Helper.cpp
* @brief
*
* @date	   2022/08/01 2022年度初版
*/
#pragma once


#include <map>
#include <array>
#include <d3d12.h>
#include "Hash.h"

/**
* 通常Map等のSTLコンテナではDirectXのDesc構造体等を管理出来ないため、作成。
* これを主に、Smapler等で使用する。
*/
template<class Key, class T>
class D3D12Map
{
public:

	T Find(const Key& key) noexcept;
	UINT Add(const Key& key, T value) noexcept;
	void Reset() noexcept;

private:

	std::map<UINT, T> m_map;
};

template<class Key, class T>
FORCEINLINE T D3D12Map<Key, T>::Find(const Key& key) noexcept
{
	UINT hash = GetHash(key);
	if (m_map.contains(hash))
	{
		return m_map[hash];
	}
	else
	{
		return T();
	}
}

template<class Key, class T>
FORCEINLINE UINT D3D12Map<Key, T>::Add(const Key& key, T value) noexcept
{
	UINT hash = GetHash(key);
	m_map[hash] = value;
	return m_map.size();
}

template<class Key, class T>
FORCEINLINE void D3D12Map<Key, T>::Reset() noexcept
{
	m_map.clear();
}

#define MAX_RENDER_TARGET 8
#define MAX_VIEWPORT 16
#define MAX_SCISSORRECT 16
#define MAX_CONSTANT_BUFFER_VIEW 16
#define MAX_SHADER_RESOURCE_VIEW 48
#define MAX_UNORDERED_ACCESS_VIEW 16
#define MAX_SAMPLER 16


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

template<typename T>
DWORD GetMsb(const T num) noexcept
{
	DWORD index = 0;
	_BitScanReverse(&index, static_cast<DWORD>(num));
	return index;
}

template<typename T>
DWORD GetLsb(const T num) noexcept
{
	DWORD index = 0;
	_BitScanForward(&index, static_cast<DWORD>(num));
	return index;
}