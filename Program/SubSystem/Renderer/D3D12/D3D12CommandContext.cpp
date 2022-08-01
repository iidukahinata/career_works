/**
* @file    D3D12CommandContext.cpp
* @brief

* @date	   2022/08/01 2022�N�x����
*/


#include "D3D12CommandContext.h"
#include "D3D12GrahicsDevice.h"
#include "D3D12View.h"
#include "D3D12Sampler.h"
#include "D3D12RootSignature.h"
#include "D3D12PipelineState.h"

bool D3D12CommandContext::Create() noexcept
{
	auto type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	HRESULT hr = GetDevice()->CreateCommandAllocator(type, IID_PPV_ARGS(m_commandAllocator.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		return false;
	}

	hr = GetDevice()->CreateCommandList(0, type, m_commandAllocator.Get(), nullptr, IID_PPV_ARGS(m_commandList.ReleaseAndGetAddressOf()));
	if (FAILED(hr)) {
		return false;
	}
	
	D3D12_COMMAND_QUEUE_DESC cmdQueueDesc = {};
	cmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;//�^�C���A�E�g�Ȃ�
	cmdQueueDesc.NodeMask = 0;
	cmdQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;//�v���C�I���e�B���Ɏw��Ȃ�
	cmdQueueDesc.Type = type;

	hr = GetDevice()->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(m_commandQueue.ReleaseAndGetAddressOf()));//�R�}���h�L���[����	
	if (FAILED(hr)) {
		return false;
	}

	m_stateCache.Create();

	return true;
}

void D3D12CommandContext::BegineFream() noexcept
{
	m_stateCache.BegineFrame();
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

void D3D12CommandContext::SetGraphicsPipelineState(D3D12GraphicsPipelineState* pipelineState) noexcept
{
	m_stateCache.SetGraphicsPipelineState(pipelineState);
}

void D3D12CommandContext::SetComputePipelineState(D3D12ComputePipelineState* pipelineState) noexcept
{
	m_stateCache.SetComputePipelineState(pipelineState);
}

void D3D12CommandContext::SetVertexBuffer(D3D12_VERTEX_BUFFER_VIEW* vertexBufferView) noexcept
{
	m_stateCache.SetVertexBuffer(vertexBufferView);
}

void D3D12CommandContext::SetIndexBuffer(D3D12_INDEX_BUFFER_VIEW* indexBufferView) noexcept
{
	m_stateCache.SetIndexBuffer(indexBufferView);
}

void D3D12CommandContext::SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY primitiveTopology) noexcept
{
	m_stateCache.SetPrimitiveTopology(primitiveTopology);
}

void D3D12CommandContext::SetRenderTargets(UINT numRenderTargets, D3D12RenderTextureView** renderTargets, D3D12DepthStencilView* depthStencil) noexcept
{
	m_stateCache.SetRenderTargets(numRenderTargets, renderTargets, depthStencil);
}

void D3D12CommandContext::SetViewPorts(UINT numViewPorts, D3D12_VIEWPORT* viewports) noexcept
{
	m_stateCache.SetViewPorts(numViewPorts, viewports);
}

void D3D12CommandContext::SetScissorRects(UINT numRects, D3D12_RECT* rects) noexcept
{
	m_stateCache.SetScissorRects(numRects, rects);
}

void D3D12CommandContext::SetConstantBuffer(ShaderType shaderType, UINT index, D3D12ConstantBufferView* constantBufferView) noexcept
{
	m_stateCache.SetConstantBuffer(shaderType, index, constantBufferView);
}

void D3D12CommandContext::SetShaderResource(ShaderType shaderType, UINT index, D3D12ShaderResourceView* shaderResourceView) noexcept
{
	m_stateCache.SetShaderResource(shaderType, index, shaderResourceView);
}

void D3D12CommandContext::SetUnorderedAccess(ShaderType shaderType, UINT index, D3D12UnorderedAccessView* unorderedAccessView) noexcept
{
	m_stateCache.SetUnorderedAccess(shaderType, index, unorderedAccessView);
}

void D3D12CommandContext::SetSampler(ShaderType shaderType, UINT index, D3D12Sampler* sampler) noexcept
{
	m_stateCache.SetSampler(shaderType, index, sampler);
}

void D3D12CommandContext::ClearRenderTargetView(D3D12RenderTextureView* renedrTarget, float* color, UINT numRects, D3D12_RECT* rects) noexcept
{
	m_commandList->ClearRenderTargetView(renedrTarget->GetCPUHandle(), color, numRects, rects);
}

void D3D12CommandContext::ClearDepthStencilView(D3D12DepthStencilView* depthStencil, D3D12_CLEAR_FLAGS clearFlags, float depth, UINT8 stencil, UINT numRects, D3D12_RECT* rects) noexcept
{
	m_commandList->ClearDepthStencilView(depthStencil->GetCPUHandle(), clearFlags, depth, stencil, numRects, rects);
}

void D3D12CommandContext::DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation) noexcept
{
	m_stateCache.Apply();
	GetCommandList()->DrawIndexedInstanced(IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}