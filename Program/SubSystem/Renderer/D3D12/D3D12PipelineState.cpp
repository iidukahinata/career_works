/**
* @file    D3D12PipelineState.cpp
* @brief
*
* @date	   2022/07/26 2022�N�x����
*/


#include "D3D12PipelineState.h"
#include "D3D12GrahicsDevice.h"

bool D3D12PipelineState::Create(const D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc) noexcept
{
	auto hr = GetDevice()->CreateGraphicsPipelineState(
		&desc,
		IID_PPV_ARGS(m_pipelineState.ReleaseAndGetAddressOf()));

	if (FAILED(hr))	{
		return false;
	}
	return true;
}

bool D3D12PipelineState::Create(const D3D12_COMPUTE_PIPELINE_STATE_DESC& desc) noexcept
{
	auto hr = GetDevice()->CreateComputePipelineState(
		&desc,
		IID_PPV_ARGS(m_pipelineState.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}
	return true;
}

void D3D12PipelineState::Set() const noexcept
{
	GetCommandList()->SetPipelineState(m_pipelineState.Get());
}