/**
* @file  Common.h
* @brief ���ʓI�ȏ������܂Ƃ߂Ă���
*
* @date	 2022/07/06 2022�N�x����
*/
#pragma once


#include "Hash.h"
#include "SubSystem/Log/DebugLog.h"


#ifdef _DEBUG
#ifdef _M_IX86 || _M_IX86_FP
#define DEBUG_BREAK _asm { int 3 }
#else
#define DEBUG_BREAK __debugbreak()
#endif // _M_IX86 || _M_IX86_FP
#else
#define DEBUG_BREAK
#endif

#define INLINE inline
#define FORCEINLINE __forceinline

#define ALIGN(N) __declspec(align(N))

#ifdef _DEBUG
#define LOG(text)		DebugLog::Get().Log(text)
#define LOG_ERROR(text)	DebugLog::Get().Error(text, __FILE__, __LINE__)

#define ASSERT(expr) \
	if (expr) {}		 \
	else {			     \
		LOG_ERROR(#expr);\
		DEBUG_BREAK;	 \
	}
#else
#define DEBUG_BREAK

#define LOG(text)
#define LOG_ERROR(text)

#define ASSERT(expr)
#endif // _DEBUG

/**
* typeid �w�肾�ƃN���X�������̂܂܂̕�����Ƃ��Ď擾�o���Ȃ����ߍ쐬�B
* �g�p�p�r�ɂ���邪�A���̃N���X�݂̂̌^��r�͐������Ȃ��B
* �����̗p�r�Ŏg�p����ꍇ�͖��O��r�������ɍs��������萳�m�ȓ����ɂȂ�B
*/
struct ClassTypeData
{
public:

	const std::string_view Name = nullptr;

	const size_t Hash = 0;

	constexpr ClassTypeData(std::string_view name, size_t hash) : Name(name), Hash(hash)
	{}

	constexpr ClassTypeData(std::string_view name) : Name(name), Hash(GetHashFromCRC(name))
	{}

	constexpr bool operator==(const ClassTypeData& typeData) const noexcept
	{
		return Hash == typeData.Hash;
	}
};