/**
* @file    Memory.h
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/


#include "Memory.h"
#include "Allocator.h"

namespace Memory
{
	static Allocator g_allocator(0x1000000U);

	void* Malloc(uint32_t size) noexcept
	{
		return g_allocator.Allocate(size);
	}

	void Free(void* ptr) noexcept
	{
		g_allocator.Deallocate(ptr);
	}
}