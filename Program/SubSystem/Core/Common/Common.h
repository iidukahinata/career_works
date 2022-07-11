/**
* @file  Common.h
* @brief ���ʓI�ȏ������܂Ƃ߂Ă���
*
* @date	 2022/07/12 2022�N�x����
*/
#pragma once


#include "Tools/Hash.h"
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
#define LOG(text)
#define LOG_ERROR(text)

#define ASSERT(expr)
#endif // _DEBUG