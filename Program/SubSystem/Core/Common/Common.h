/**
* @file  Common.h
* @brief 共通的な処理をまとめている
*
* @date	 2022/06/13 2022年度初版
*/
#pragma once


#include "SubSystem/Log/DebugLog.h"

// libファイルをまとめて管理する。
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "DirectXTex.lib")
#pragma comment(lib, "assimp-vc141-mtd.lib")
#pragma comment(lib, "fmodL_vc.lib")
#pragma comment(lib, "BulletCollision.lib")
#pragma comment(lib, "BulletDynamics.lib")
#pragma comment(lib, "BulletSoftBody.lib")
#pragma comment(lib, "LinearMath.lib")


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

#define ALIGN(i) __declspec(align(i))

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

struct CompileData
{
public:

	const char* className = nullptr;

	const uint32_t classSize = 0;

	const uint32_t hashID = 0;

	constexpr CompileData(const char* name, uint32_t size, uint32_t hash) : className(name), classSize(size), hashID(hash)
	{}
};