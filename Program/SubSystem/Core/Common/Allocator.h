/**
* @file    Allocator.h
* @brief   
*
* @date	   2022/07/05 2022�N�x����
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

	// * ���J�e�S���̕�����
	uint32_t m_numOfDivisions /* = pow(2, N) */;

	// * �m�ۂ���Pool�̐擪�|�C���^
	void* m_memory = nullptr;

	// * ���J�e�S���̏����������t���O
	uint32_t m_globalFLI = 0;

	// * ���J�e�S���̏����������t���O
	std::vector<uint32_t> m_freeListBits;

	// * ����U��\�ȃt���[���������X�g
	std::vector<BoundaryBlock*> m_freeLists;
};