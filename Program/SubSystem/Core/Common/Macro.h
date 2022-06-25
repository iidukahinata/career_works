/**
* @file  Macro.h
* @brief ã§í ìIÇ»èàóùÇÇ‹Ç∆ÇﬂÇƒÇ¢ÇÈ
*
* @date	 2022/06/25 2022îNìxèâî≈
*/
#pragma once


#include <typeinfo>
#include "Common.h"

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