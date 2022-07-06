/**
* @file    D3D12CommandContext.cpp
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/


#include "D3D12CommandContext.h"
#include "D3D12GrahicsDevice.h"

bool D3D12CommandContext::Create() noexcept
{
	auto device = GetGraphicsDevice()->GetDevice();

	HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(m_commandAllocator.ReleaseAndGetAddressOf()));

	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		m_commandAllocator.Get(),
		nullptr,
		IID_PPV_ARGS(m_commandList.ReleaseAndGetAddressOf()));

	if (FAILED(hr))
	{
		return false;
	}

	// �R�}���h���X�g�͍쐬���ꂽ���_�ŊJ���Ă�̂ŕ���
	m_commandList->Close();

	// ��������R�}���h�L���[�̐ݒ�
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc = {};
	commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	hr = device->CreateCommandQueue(
		&commandQueueDesc,
		IID_PPV_ARGS(m_commandQueue.ReleaseAndGetAddressOf()));

	if (FAILED(hr))
	{
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

void D3D12CommandContext::Clear(ID3D12PipelineState* const pPipelineSate /* = nullptr */) noexcept
{
	m_commandAllocator->Reset();
	m_commandList->Reset(m_commandAllocator.Get(), pPipelineSate);
}

bool D3D12CommandContext::Signal(ID3D12Fence* const pFence, const UINT64& currentFenceValue) noexcept
{
	if (SUCCEEDED(m_commandQueue->Signal(pFence, currentFenceValue)))
	{
		return true;
	}
	return false;
}