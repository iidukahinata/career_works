/**
* @file    Allocator.h
* @brief   
*
* @date	   2022/07/19 2022�N�x����
*/
#pragma once


typedef unsigned long ulong;
class BoundaryBlock;

class Allocator
{
public:

	Allocator(uint32_t memorySize);
	~Allocator();

	void* Allocate(uint32_t size) noexcept;
	void Deallocate(void* ptr) noexcept;

private:

	ulong GetMsb(const uint32_t num) const noexcept;
	ulong GetLsb(const uint32_t num) const noexcept;

	ulong GetSecondCategory(const uint32_t num, const uint32_t msb) const noexcept;

	/** 
	* �t���[���X�g�� bit �ȏ�̃������T�C�Y��ێ����邩�𔻕ʁB
	* @param listBit �ɂ� FLI �������� SLI Bit����w�肵�Ă��������B
	* @return �t���[���X�g�����݂���ꍇ���� ID ��Ԃ��B
	*/
	uint8_t GetFreeListToCategory(const uint8_t bit, const uint32_t listBit) const noexcept;

	/**
	* �����l����t���[���X�g�I�u�W�F�N�g���������擾�B
	* �����w��I�u�W�F�N�g�������ꍇ�A�X�ɑ傫�ȃ��������������ɂ����B
	*/
	BoundaryBlock* GetFreeList(uint32_t fli, uint32_t sli) const noexcept;

	/** �t���[���X�g���� */
	void AddToFreeList(BoundaryBlock* block) noexcept;
	void RemoveFromFreeList(BoundaryBlock* block) noexcept;

private:

	const uint32_t N = 4;

	// * ���J�e�S���̕�����
	uint32_t m_numOfDivisions /* = pow(2, N) */;

	// * �m�ۂ���Pool�̐擪�|�C���^
	void* m_memory = nullptr;

	uint32_t m_maxMemorySize;

	// * ���J�e�S���̏����������t���O
	uint32_t m_globalFLI = 0;

	// * ���J�e�S���̏����������t���O
	uint32_t* m_freeListBits;

	// * ����U��\�ȃt���[���������X�g
	BoundaryBlock** m_freeLists;
};