/**
* @file    D3D12DescriptorAllocator.h
* @brief
*
* @date	   2022/08/01 2022�N�x����
*/
#pragma once


#include <vector>
#include <memory>
#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12DescriptorAllocator;

class D3D12Descriptor
{
public:

	// * Allocator�e�[�u���̊e�������ʒu
	D3D12_CPU_DESCRIPTOR_HANDLE	m_cpuHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE	m_gpuHandle;

public:

	D3D12Descriptor(
		D3D12DescriptorAllocator* allocator,
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle,
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle) noexcept;

	void AddRef() noexcept;
	void Release() noexcept;

private:

	// * ���g�̉�������Ŏg�p
	D3D12DescriptorAllocator* m_allocator;

	UINT m_refCount = 0;
};

//
// D3D12DescriptorAllocator
//

class D3D12DescriptorAllocator : public D3D12DeviceChild
{
public:

	~D3D12DescriptorAllocator();
	bool Initialize(UINT numDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept;
	void Release() noexcept;

	D3D12Descriptor* Allocate() noexcept;
	void Deallocate(D3D12Descriptor* ptr) noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_descriptHeap;

	// * �������ݒ�
	UINT m_incrementSize;
	UINT m_numDescriptors;
	D3D12_DESCRIPTOR_HEAP_TYPE m_heapType;

	// * ���������p�ӂ���Descript�T�C�Y�͈͊O�A�N�Z�X��h�����ߊĎ�
	UINT m_currentPosition;

	// * ���쐬�����Descriptor���ێ����郁�����ʒu
	D3D12_CPU_DESCRIPTOR_HANDLE	m_cpuBackHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE	m_gpuBackHandle;

	// * ������ꂽDescriptor���ė��p���邽�߂Ɏg�p
	std::vector<D3D12Descriptor*> m_freeList;

	// * �������ꂽ�S�Ă�Descriptor���Ǘ�
	std::vector<std::unique_ptr<D3D12Descriptor>> m_descripts;
};

//
// D3D12GlobalDescriptorHeapBlock
//

class D3D12GlobalDescriptorHeapBlock
{
public:

	D3D12GlobalDescriptorHeapBlock(
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle,
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle,
		UINT incrementSize,
		UINT blockSize);

	bool Allocate(UINT size, D3D12_CPU_DESCRIPTOR_HANDLE* cpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE* gpuHandle) noexcept;
	void Reset() noexcept;

private:

	// * �u���b�N���ێ�����Handle�T�C�Y
	UINT m_blockSize;

	UINT m_incrementSize;

	// * ���������p�ӂ���Descript�T�C�Y�͈͊O�A�N�Z�X��h�����ߊĎ�
	UINT m_currentPosition;

	// * ���쐬�����Descriptor���ێ����郁�����ʒu
	D3D12_CPU_DESCRIPTOR_HANDLE	m_cpuBaseHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE	m_gpuBaseHandle;
};

//
// D3D12GlobalDescriptorHeap
//

class D3D12GlobalDescriptorHeap : public D3D12DeviceChild
{
public:

	bool Initialilze(UINT totalSize, D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept;

	D3D12GlobalDescriptorHeapBlock* Allocate() noexcept;
	void Deallocate(D3D12GlobalDescriptorHeapBlock* ptr) noexcept;

	/** �A�N�Z�X */
	ID3D12DescriptorHeap* GetHeap() const noexcept { return m_descriptHeap.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_descriptHeap;

	// * �������ݒ�
	const UINT m_splitSize = 2000;
	UINT m_incrementSize;
	UINT m_numDescriptors;
	D3D12_DESCRIPTOR_HEAP_TYPE m_heapType;

	// * ���������p�ӂ���Descript�T�C�Y�͈͊O�A�N�Z�X��h�����ߊĎ�
	UINT m_currentPosition;

	// * ���쐬�����Block���ێ����郁�����ʒu
	D3D12_CPU_DESCRIPTOR_HANDLE	m_cpuCurrentHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE	m_gpuCurrentHandle;

	// * ������ꂽBlock���ė��p���邽�߂Ɏg�p
	std::vector<D3D12GlobalDescriptorHeapBlock*> m_freeBlocks;

	// * Allocate�Ő������ꂽBlock���Ǘ�
	std::vector<std::unique_ptr<D3D12GlobalDescriptorHeapBlock>> m_blocks;
};

//
// D3D12GlobalSamplerDescriptorHeap
//

/** GlobalDescriptor �̊e�u���b�N���Ǘ� */
class D3D12GlobalAllocatedDescriptorHeap
{
public:

	void Initialilze(D3D12GlobalDescriptorHeap* globalDescriptHeap) noexcept;

	void Allocate(UINT size, D3D12_CPU_DESCRIPTOR_HANDLE* cpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE* gpuHandle) noexcept;
	void Reset() noexcept;

private:

	// * �u���b�N���擾���邽�ߕێ�
	D3D12GlobalDescriptorHeap* m_globalDescriptHeap;

	// * �g�p���̃u���b�N�C���f�b�N�X
	UINT m_blockIndex;

	std::vector<D3D12GlobalDescriptorHeapBlock*> m_blocks;
};

//
// D3D12GlobalSamplerDescriptorHeap
//

class D3D12GlobalSamplerDescriptorHeap : public D3D12DeviceChild
{
public:

	bool Initialilze() noexcept;

	void Allocate(UINT size, D3D12_CPU_DESCRIPTOR_HANDLE* cpuHandle, D3D12_GPU_DESCRIPTOR_HANDLE* gpuHandle) noexcept;

	/** �A�N�Z�X */
	ID3D12DescriptorHeap* GetHeap() const noexcept { return m_descriptHeap.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_descriptHeap;

	// * ���쐬�����Block���ێ����郁�����ʒu
	D3D12_CPU_DESCRIPTOR_HANDLE	m_cpuCurrentHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE	m_gpuCurrentHandle;

	// * Sampler �Ƃ��Ċm�ۂł���Descriptor�̍ő�T�C�Y
	const UINT m_numDescriptors = 2048;

	UINT m_incrementSize = 0;
	UINT m_currentPosition = 0;
};