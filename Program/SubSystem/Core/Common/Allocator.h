/**
* @file    Allocator.h
* @brief   
*
* @date	   2022/07/05 2022年度初版
*/
#pragma once


#include <vector>

using ulong = unsigned long;
class BoundaryBlock;

class Allocator
{
public:

	void Initialize();
	~Allocator();

	void* Allocate(uint32_t size) noexcept;
	void Deallocate(void* ptr) noexcept;

private:

	ulong GetMsb(const uint32_t num) const noexcept;
	ulong GetLsb(const uint32_t num) const noexcept;

	ulong GetSecondCategory(const uint32_t num, const uint32_t msb) const noexcept;
	uint8_t GetFreeListToCategory(const uint8_t bit, const uint32_t listBit) const noexcept;

	BoundaryBlock* GetFreeList(uint32_t fli, uint32_t sli) const noexcept;

	void AddToFreeList(BoundaryBlock* block) noexcept;
	void RemoveFromFreeList(BoundaryBlock* block) noexcept;

private:

	const uint32_t N = 4;

	// * 第二カテゴリの分割数
	uint32_t m_numOfDivisions /* = pow(2, N) */;

	// * 確保したPoolの先頭ポインタ
	void* m_memory = nullptr;

	// * 第一カテゴリの所持メモリフラグ
	uint32_t m_globalFLI = 0;

	// * 第二カテゴリの所持メモリフラグ
	std::vector<uint32_t> m_freeListBits;

	// * 割り振り可能なフリーメモリリスト
	std::vector<BoundaryBlock*> m_freeLists;
};