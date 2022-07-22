/**
* @file    D3D12DescriptorHeap.cpp
* @brief
*
* @date	   2022/07/22 2022�N�x����
*/


#include "D3D12DescriptorHeap.h"
#include "D3D12GrahicsDevice.h"

bool D3D12DescriptorHeap::Create(UINT NumDescriptors, D3D12_DESCRIPTOR_HEAP_TYPE type) noexcept
{
	D3D12_DESCRIPTOR_HEAP_DESC descriptHeapDesc = {};
	descriptHeapDesc.NumDescriptors = NumDescriptors;
	descriptHeapDesc.Type = type;
	descriptHeapDesc.NodeMask = 0;
	descriptHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	HRESULT hr = GetDevice()->CreateDescriptorHeap(
		&descriptHeapDesc,
		IID_PPV_ARGS(m_descriptHeap.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		LOG_ERROR("�f�B�X�N���v�^�q�[�v�̍쐬�����s���܂����B");
		return false;
	}

	m_d12DescriptorSize = GetDevice()->GetDescriptorHandleIncrementSize(type);
	return true;
}

void D3D12DescriptorHeap::Set()
{
	GetContext()->GetCommandList()->SetDescriptorHeaps(1, m_descriptHeap.GetAddressOf());
	GetContext()->GetCommandList()->SetGraphicsRootDescriptorTable(1, m_descriptHeap->GetGPUDescriptorHandleForHeapStart());
}

UINT D3D12DescriptorHeap::IncrementSize()
{
	return m_d12DescriptorSize;
}

D3D12_CPU_DESCRIPTOR_HANDLE D3D12DescriptorHeap::GetCPUDescriptorHandleForHeapStart()
{
	return m_descriptHeap->GetCPUDescriptorHandleForHeapStart();
}