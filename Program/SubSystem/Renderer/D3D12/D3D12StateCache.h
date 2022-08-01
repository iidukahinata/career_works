/**
* @file    D3D12StateCache.h
* @brief
*
* @date	   2022/08/01 2022�N�x����
*/
#pragma once


#include <d3d12.h>
#include "D3D12Helper.h"
#include "D3D12DeviceChild.h"
#include "D3D12DescriptorCache.h"

class D3D12GraphicsPipelineState;
class D3D12ComputePipelineState;
class D3D12RootSignature;
class D3D12ConstantBufferView;
class D3D12ShaderResourceView;
class D3D12UnorderedAccessView;
class D3D12RenderTextureView;
class D3D12DepthStencilView;
class D3D12Sampler;

struct ConstantBufferViewCache
{
	void Clear() noexcept
	{
		ZeroMemory(views.data(), sizeof(views.data()));
		ZeroMemory(indexMasks.data(), sizeof(indexMasks.data()));
	}

	Array<D3D12ConstantBufferView*, ShaderType::Max, MAX_CONSTANT_BUFFER_VIEW> views;
	Array<UINT16, ShaderType::Max> indexMasks;
};

struct ShaderResourceViewCache
{
	void Clear() noexcept
	{
		ZeroMemory(views.data(), sizeof(views.data()));
		ZeroMemory(indexMasks.data(), sizeof(indexMasks.data()));
	}

	Array<D3D12ShaderResourceView*, ShaderType::Max, MAX_SHADER_RESOURCE_VIEW> views;
	Array<UINT64, ShaderType::Max> indexMasks;
};

struct UnorderedAccessViewCache
{
	void Clear() noexcept
	{
		ZeroMemory(views.data(), sizeof(views.data()));
		ZeroMemory(indexMasks.data(), sizeof(indexMasks.data()));
	}

	Array<D3D12UnorderedAccessView*, ShaderType::Max, MAX_UNORDERED_ACCESS_VIEW> views;
	Array<UINT16, ShaderType::Max>  indexMasks;
};

struct SamplerCache
{
	void Clear() noexcept
	{
		ZeroMemory(views.data(), sizeof(views.data()));
		ZeroMemory(indexMasks.data(), sizeof(indexMasks.data()));
	}

	Array<D3D12Sampler*, ShaderType::Max, MAX_SAMPLER> views;
	Array<UINT16, ShaderType::Max>  indexMasks;
};

struct PipelineState
{
	// * pso
	ID3D12PipelineState* m_pipelineState;
	D3D12RootSignature* m_rootSignature;

	// * geometry
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
	D3D12_INDEX_BUFFER_VIEW m_indexBufferView;

	// * primitive
	D3D_PRIMITIVE_TOPOLOGY m_primitiveTopology;

	// * render target
	UINT m_numRenderTargets;
	Array<D3D12RenderTextureView*, MAX_RENDER_TARGET> m_renderTargets;

	// * depth stencil
	D3D12DepthStencilView* m_depthStencil;

	// view port
	UINT m_numViewports;
	Array<D3D12_VIEWPORT, MAX_VIEWPORT> m_viewports;

	// * scissor rect
	UINT m_numScissorRects;
	Array<D3D12_RECT, MAX_SCISSORRECT> m_scissorRects;

	// * views cache
	ConstantBufferViewCache m_cbvCache;
	ShaderResourceViewCache m_srvCache;
	UnorderedAccessViewCache m_uavCache;
	SamplerCache m_samplerCache;
};

class D3D12StateCache : public D3D12DeviceChild
{
public:

	void Create() noexcept;
	void BegineFrame() noexcept;

	void Apply() noexcept;

	/** pipelineState */
	void SetGraphicsPipelineState(D3D12GraphicsPipelineState* pipelineState) noexcept;
	void SetComputePipelineState(D3D12ComputePipelineState* pipelineState) noexcept;

	/** geometry */
	void SetVertexBuffer(D3D12_VERTEX_BUFFER_VIEW* vertexBufferView) noexcept;
	void SetIndexBuffer(D3D12_INDEX_BUFFER_VIEW* indexBufferView) noexcept;

	/** primitive */
	void SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY primitiveTopology) noexcept;

	/** renderTargets */
	void SetRenderTargets(UINT numRenderTargets, D3D12RenderTextureView** renderTargets, D3D12DepthStencilView* depthStencil) noexcept;
	void SetViewPorts(UINT numViewPorts, D3D12_VIEWPORT* viewports) noexcept;
	void SetScissorRects(UINT numScissorRects, D3D12_RECT* scissorRects) noexcept;

	/** descriptor */
	void SetConstantBuffer(ShaderType shaderType, UINT index, D3D12ConstantBufferView* constantBufferView) noexcept;
	void SetShaderResource(ShaderType shaderType, UINT index, D3D12ShaderResourceView* shaderResourceView) noexcept;
	void SetUnorderedAccess(ShaderType shaderType, UINT index, D3D12UnorderedAccessView* unorderedAccessView) noexcept;
	void SetSampler(ShaderType shaderType, UINT index, D3D12Sampler* sampler) noexcept;

private:

	void Flush() noexcept;

private:

	// * Descriptor ���̃Z�b�g��
	D3D12DescriptorCache m_descriptorCache;

	// * ����h���[�R�[�����ݒ�
	PipelineState m_state;

	// * set falgs
	bool m_setPipelineState;
	bool m_setRootSignature;
	bool m_setVertexBuffer;
	bool m_setIndexBuffer;
	bool m_setPrimitiveTopology;
	bool m_setRenderTargets;
	bool m_setViewports;
	bool m_setScissorRects;
};