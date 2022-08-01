/**
* @file    D3D12CommandContext.h
* @brief
*
* @date	   2022/07/30 2022�N�x����
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"
#include "D3D12StateCache.h"

class D3D12Fence : public D3D12DeviceChild
{
public:

	UINT64 m_fenceValue = 0;

public:

	~D3D12Fence();

	bool Create() noexcept;
	void WaitForSingleToFinish() noexcept;

	/** �A�N�Z�X */
	ID3D12Fence* Get() const noexcept { return m_fence.Get(); }

private:

	// * GPU�Ƃ̓����Ɏg�p
	Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;

	// * GPU�����ҋ@�pWinAPIEvent
	HANDLE m_fenceEvent;
};

class D3D12CommandContext : public D3D12DeviceChild
{
public:

	bool Create() noexcept;

	void BegineFream() noexcept;
	void RunCommandList() noexcept;
	void Clear(ID3D12PipelineState* const pPipelineSate = nullptr) noexcept;
	bool Signal(ID3D12Fence* const pFence, const UINT64& currentFenceValue) noexcept;

	/** set state */
	void SetGraphicsPipelineState(D3D12GraphicsPipelineState* pipelineState) noexcept;
	void SetComputePipelineState(D3D12ComputePipelineState* pipelineState) noexcept;
	void SetVertexBuffer(D3D12_VERTEX_BUFFER_VIEW* vertexBufferView) noexcept;
	void SetIndexBuffer(D3D12_INDEX_BUFFER_VIEW* indexBufferView) noexcept;
	void SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY primitiveTopology) noexcept;
	void SetRenderTargets(UINT numRenderTargets, D3D12RenderTextureView** renderTargets, D3D12DepthStencilView* depthStencil) noexcept;
	void SetViewPorts(UINT numViewPorts, D3D12_VIEWPORT* viewports) noexcept;
	void SetScissorRects(UINT numRects, D3D12_RECT* rects) noexcept;
	void SetConstantBuffer(ShaderType shaderType, UINT index, D3D12ConstantBufferView* constantBufferView) noexcept;
	void SetShaderResource(ShaderType shaderType, UINT index, D3D12ShaderResourceView* shaderResourceView) noexcept;
	void SetUnorderedAccess(ShaderType shaderType, UINT index, D3D12UnorderedAccessView* unorderedAccessView) noexcept;
	void SetSampler(ShaderType shaderType, UINT index, D3D12Sampler* sampler) noexcept;

	/** �N���A */
	void ClearRenderTargetView(D3D12RenderTextureView* renedrTarget, float* color, UINT numRects, D3D12_RECT* rects) noexcept;
	void ClearDepthStencilView(D3D12DepthStencilView* depthStencil, D3D12_CLEAR_FLAGS clearFlags, float depth, UINT8 stencil, UINT numRects, D3D12_RECT* rects) noexcept;

	/** �h���[�R�[�� */
	void DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation) noexcept;

	/** �A�N�Z�X */
	ID3D12GraphicsCommandList* GetCommandList()      const noexcept { return m_commandList.Get(); }
	ID3D12CommandQueue*		   GetCommandQueue()     const noexcept { return m_commandQueue.Get(); }
	ID3D12CommandAllocator*	   GetCommandAllocator() const noexcept { return m_commandAllocator.Get(); }

private:

	// * GPU�ɖ��߂��郁�\�b�h���L�q���Ă���
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;

	// * �R�}���h�̋L���̈�
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_commandAllocator;

	// * ���ۂ�GPU�Ƀf�[�^��n�� object
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;

	// * �h���[�R�[���܂ŕ`��ݒ���ꎞ�ۑ�������ꕨ
	D3D12StateCache m_stateCache;
};