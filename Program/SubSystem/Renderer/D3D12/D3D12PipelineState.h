/**
* @file    D3D12PipelineState.h
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12PipelineState : public D3D12DeviceChild
{
public:

	bool Create(const D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc) noexcept;
	bool Create(const D3D12_COMPUTE_PIPELINE_STATE_DESC& desc) noexcept;
	void Set() const noexcept;

	ID3D12PipelineState* Get() const noexcept { return m_pipelineState.Get(); };

private:

	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState;
};