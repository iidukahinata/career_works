/**
* @file  Macro.h
* @brief 共通的な処理をまとめている
*
* @date	 2022/07/12 2022年度初版
*/
#pragma once


#include <typeinfo>
#include "Common.h"

/**
* typeid 指定だとクラス名をそのままの文字列として取得出来ないため作成。
* 使用用途にもよるが、このクラスのみの型比較は推奨しない。
* それらの用途で使用する場合は名前比較も同時に行う方がより正確な答えになる。
*/
struct ClassTypeData
{
	const StringView Name = nullptr;

	const size_t Hash = 0;

	constexpr ClassTypeData(StringView name, size_t hash) : Name(name), Hash(hash)
	{}

	constexpr ClassTypeData(StringView name) : Name(name), Hash(GetHashFromCRC(name))
	{}

	constexpr bool operator==(const ClassTypeData& typeData) const noexcept
	{
		return Hash == typeData.Hash;
	}
};


#define COPY_PROHIBITED(CLASS)			\
CLASS(const CLASS&) = delete;			\
CLASS& operator=(const CLASS&) = delete;

#define CLASS_DATA(CLASS) \
static INLINE ClassTypeData TypeData = ClassTypeData(#CLASS, GET_HASH(CLASS));

#define SUPER_CLASS(CLASS)						\
public:											\
CLASS_DATA(CLASS)								\
virtual const ClassTypeData& GetTypeData() const\
{												\
	return TypeData;							\
}												\
const std::type_info& TypeInfo() noexcept		\
{												\
	return typeid(*this);						\
}

#define SUB_CLASS(CLASS)							\
public:												\
CLASS_DATA(CLASS)									\
const ClassTypeData& GetTypeData() const override	\
{													\
	return TypeData;								\
}