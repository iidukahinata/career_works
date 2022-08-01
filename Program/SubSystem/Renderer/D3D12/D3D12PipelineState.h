/**
* @file    D3D12PipelineState.h
* @brief
*
* @date	   2022/07/31 2022年度初版
*/
#pragma once


#include "D3D12DeviceChild.h"
#include "D3D12RootSignature.h"

class D3D12GraphicsPipelineState : public D3D12DeviceChild
{
public:

	bool Create(const D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc, D3D12RootSignature* rootSignature) noexcept;
	void Set() noexcept;

	/** アクセス */
	ID3D12PipelineState* Get()				const noexcept { return m_pipelineState.Get(); }
	D3D12RootSignature*  GetRootSignature() const noexcept { return m_rootSignature; }

private:

	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState;

	D3D12RootSignature* m_rootSignature = nullptr;
};

class D3D12ComputePipelineState : public D3D12DeviceChild
{
public:

	bool Create(const D3D12_COMPUTE_PIPELINE_STATE_DESC& desc) noexcept;
	void Set() noexcept;

	/** アクセス */
	ID3D12PipelineState* Get() const noexcept { return m_pipelineState.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D12PipelineState> m_pipelineState;
};