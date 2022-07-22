/**
* @file    D3D12CommandContext.h
* @brief
*
* @date	   2022/07/22 2022�N�x����
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12Fence : public D3D12DeviceChild
{
public:

	UINT64 m_fenceValue = 0;

public:

	~D3D12Fence();

	bool Create() noexcept;
	void WaitForSingleToFinish() noexcept;

	ID3D12Fence* Get() const noexcept { return m_fence.Get(); }

private:

	// * GPU�Ƃ̓����Ɏg�p
	Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;

	HANDLE m_fenceEvent;
};

class D3D12CommandContext : public D3D12DeviceChild
{
public:

	bool Create() noexcept;
	void RunCommandList() noexcept;
	void Clear(ID3D12PipelineState* const pPipelineSate = nullptr) noexcept;
	bool Signal(ID3D12Fence* const pFence, const UINT64& currentFenceValue) noexcept;

	ID3D12GraphicsCommandList* GetCommandList()      const noexcept { return m_commandList.Get(); };
	ID3D12CommandQueue*        GetCommandQueue()     const noexcept { return m_commandQueue.Get(); };
	ID3D12CommandAllocator*    GetCommandAllocator() const noexcept { return m_commandAllocator.Get(); };

private:

	// * GPU�ɖ��߂��郁�\�b�h���L�q���Ă���
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;

	// * �R�}���h�̋L���̈�
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocator;

	// * ���ۂ�GPU�Ƀf�[�^��n�� object
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
};