#pragma once


#include <typeinfo>
#include "Hash.h"
#include "Common.h"

#define COPY_PROHIBITED(CLASS)			\
CLASS(const CLASS&) = delete;			\
CLASS& operator=(const CLASS&) = delete;

#define CLASS_DATA(CLASS)												\
static constexpr CompileData ClassData() noexcept						\
{																		\
	return CompileData(#CLASS, sizeof(CLASS), GetHashFromCRC(#CLASS));	\
}

#define SUPER_CLASS(CLASS)				\
public:									\
CLASS_DATA(CLASS)						\
const std::type_info& TypeInfo() const	\
{										\
	return typeid(*this);				\
}

#define SUB_CLASS(CLASS)\
public:					\
CLASS_DATA(CLASS)