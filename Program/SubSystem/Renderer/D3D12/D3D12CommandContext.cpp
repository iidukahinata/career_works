/**
* @file    D3D12CommandContext.cpp
* @brief
*
* @date	   2022/07/26 2022�N�x����
*/


#include "D3D12CommandContext.h"
#include "D3D12GrahicsDevice.h"

bool D3D12CommandContext::Create() noexcept
{
	auto hr = GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(m_commandAllocator.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		return false;
	}

	hr = GetDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), nullptr, IID_PPV_ARGS(m_commandList.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		return false;
	}
	
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;//�^�C���A�E�g�Ȃ�
	cmdQueueDesc.NodeMask = 0;
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;//�v���C�I���e�B���Ɏw��Ȃ�
	cmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;//�����̓R�}���h���X�g�ƍ��킹�Ă�������
	hr = GetDevice()->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(m_commandQueue.ReleaseAndGetAddressOf()));//�R�}���h�L���[����
	
	if (FAILED(hr)) {
		return false;
	}

	return true;
}

void D3D12CommandContext::RunCommandList() noexcept
{
	// ��t���I��
	m_commandList->Close();

	// �R�}���h���X�g��GPU�ɑ��M����
	ID3D12CommandList* cmdlists[] = { m_commandList.Get() };
	m_commandQueue->ExecuteCommandLists(_countof(cmdlists), cmdlists);
}

void D3D12CommandContext::Clear(ID3D12PipelineState* pipelineSate /* = nullptr */) noexcept
{
	m_commandAllocator->Reset();
	m_commandList->Reset(m_commandAllocator.Get(), pipelineSate);
}

bool D3D12CommandContext::Signal(ID3D12Fence* fence, UINT64 currentFenceValue) noexcept
{
	if (SUCCEEDED(m_commandQueue->Signal(fence, currentFenceValue)))
	{
		return true;
	}
	return false;
}