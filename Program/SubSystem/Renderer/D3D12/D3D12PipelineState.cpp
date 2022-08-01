/**
* @file    D3D12PipelineState.cpp
* @brief
*
* @date	   2022/07/31 2022”N“x‰”Å
*/


#include "D3D12PipelineState.h"
#include "D3D12GrahicsDevice.h"

bool D3D12GraphicsPipelineState::Create(const D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc, D3D12RootSignature* rootSignature) noexcept
{
	HRESULT hr = GetDevice()->CreateGraphicsPipelineState(
		&desc,
		IID_PPV_ARGS(m_pipelineState.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}

	m_rootSignature = rootSignature;

	return true;
}

void D3D12GraphicsPipelineState::Set() noexcept
{
	GetCommandContext()->SetGraphicsPipelineState(this);
}

bool D3D12ComputePipelineState::Create(const D3D12_COMPUTE_PIPELINE_STATE_DESC& desc) noexcept
{
	HRESULT hr = GetDevice()->CreateComputePipelineState(
		&desc,
		IID_PPV_ARGS(m_pipelineState.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}
	return true;
}

void D3D12ComputePipelineState::Set() noexcept
{
	GetCommandContext()->SetComputePipelineState(this);
}