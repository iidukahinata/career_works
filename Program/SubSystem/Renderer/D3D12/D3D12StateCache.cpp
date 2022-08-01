/**
* @file    D3D12StateCache.cpp
* @brief

* @date	   2022/08/01 2022”N“x‰”Å
*/


#include "D3D12StateCache.h"
#include "D3D12View.h"
#include "D3D12Sampler.h"
#include "D3D12RootSignature.h"
#include "D3D12PipelineState.h"
#include "D3D12CommandContext.h"

void D3D12StateCache::Create() noexcept
{
	m_descriptorCache.Create();
}

void D3D12StateCache::BegineFrame() noexcept
{
	m_descriptorCache.BegineFrame();
}

void D3D12StateCache::Apply() noexcept
{
	// PSO
	{
		if (m_setRootSignature)
		{
			GetCommandContext()->GetCommandList()->SetGraphicsRootSignature(m_state.m_rootSignature->Get());
		}

		if (m_setPipelineState)
		{
			GetCommandContext()->GetCommandList()->SetPipelineState(m_state.m_pipelineState);
		}
	}

	// not has Heap bindings
	{
		if (m_setVertexBuffer)
		{
			GetCommandContext()->GetCommandList()->IASetVertexBuffers(0, 1, &m_state.m_vertexBufferView);
		}
		if (m_setIndexBuffer)
		{
			GetCommandContext()->GetCommandList()->IASetIndexBuffer(&m_state.m_indexBufferView);
		}
		if (m_setPrimitiveTopology)
		{
			GetCommandContext()->GetCommandList()->IASetPrimitiveTopology(m_state.m_primitiveTopology);
		}
		if (m_setRenderTargets)
		{
			m_descriptorCache.SetRenderTargets(m_state.m_numRenderTargets, m_state.m_renderTargets.data(), m_state.m_depthStencil);
		}
		if (m_setViewports)
		{
			GetCommandContext()->GetCommandList()->RSSetViewports(m_state.m_numViewports, m_state.m_viewports.data());
		}
		if (m_setScissorRects)
		{
			GetCommandContext()->GetCommandList()->RSSetScissorRects(m_state.m_numScissorRects, m_state.m_scissorRects.data());
		}
	}

	// has Heap bindings
	{
		m_descriptorCache.SetDescriptorHeap();

		auto SetSampler = [this](ShaderType type) {
			m_descriptorCache.SetSampler(type, m_state.m_samplerCache, m_state.m_rootSignature);
		};

		SetSampler(ShaderType::VertexShader);
		SetSampler(ShaderType::PixelShader);
		SetSampler(ShaderType::GeometryShader);

		auto SetViews = [this](ShaderType type) {
			m_descriptorCache.SetConstantBufferView(type, m_state.m_cbvCache, m_state.m_rootSignature);
			m_descriptorCache.SetShaderResourceView(type, m_state.m_srvCache, m_state.m_rootSignature);
			m_descriptorCache.SetUnorderedAccessView(type, m_state.m_uavCache, m_state.m_rootSignature);
		};

		SetViews(ShaderType::VertexShader);
		SetViews(ShaderType::PixelShader);
		SetViews(ShaderType::GeometryShader);
	}

	Flush();
}

void D3D12StateCache::SetGraphicsPipelineState(D3D12GraphicsPipelineState* pipelineState) noexcept
{
	//assert(pipelineState);

	m_state.m_rootSignature = pipelineState->GetRootSignature();
	m_setRootSignature = true;

	m_state.m_pipelineState = pipelineState->Get();
	m_setPipelineState = true;
}

void D3D12StateCache::SetComputePipelineState(D3D12ComputePipelineState* pipelineState) noexcept
{
	//assert(pipelineState);

	m_state.m_pipelineState = pipelineState->Get();
	m_setPipelineState = true;
}

void D3D12StateCache::SetVertexBuffer(D3D12_VERTEX_BUFFER_VIEW* vertexBufferView) noexcept
{
	//assert(vertexBufferView);

	m_state.m_vertexBufferView.BufferLocation = vertexBufferView->BufferLocation;
	m_state.m_vertexBufferView.StrideInBytes = vertexBufferView->StrideInBytes;
	m_state.m_vertexBufferView.SizeInBytes = vertexBufferView->SizeInBytes;
	m_setVertexBuffer = true;
}

void D3D12StateCache::SetIndexBuffer(D3D12_INDEX_BUFFER_VIEW* indexBufferView) noexcept
{
	//assert(indexBufferView);

	m_state.m_indexBufferView.BufferLocation = indexBufferView->BufferLocation;
	m_state.m_indexBufferView.Format = indexBufferView->Format;
	m_state.m_indexBufferView.SizeInBytes = indexBufferView->SizeInBytes;
	m_setIndexBuffer = true;
}

void D3D12StateCache::SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY primitiveTopology) noexcept
{
	m_state.m_primitiveTopology = primitiveTopology;
	m_setPrimitiveTopology = true;
}

void D3D12StateCache::SetRenderTargets(UINT numRenderTargets, D3D12RenderTextureView** renderTargets, D3D12DepthStencilView* depthStencil) noexcept
{
	//assert(numRenderTargets < MAX_RENDER_TARGET);
	//assert(renderTargets);
	//assert(depthStencil);

	constexpr UINT maxSize = sizeof(D3D12RenderTextureView*) * MAX_RENDER_TARGET;

	m_state.m_depthStencil = depthStencil;
	m_state.m_numRenderTargets = numRenderTargets;
	memcpy_s(m_state.m_renderTargets.data(), maxSize, renderTargets, sizeof(D3D12RenderTextureView) * numRenderTargets);

	m_setRenderTargets = true;
}

void D3D12StateCache::SetViewPorts(UINT numViewPorts, D3D12_VIEWPORT* viewports) noexcept
{
	//assert(numViewPorts < MAX_VIEWPORT);
	//assert(viewports);

	constexpr UINT maxSize = sizeof(D3D12_VIEWPORT) * MAX_VIEWPORT;

	m_state.m_numViewports = numViewPorts;
	memcpy_s(m_state.m_viewports.data(), maxSize, viewports, sizeof(D3D12_VIEWPORT) * numViewPorts);

	m_setViewports = true;
}

void D3D12StateCache::SetScissorRects(UINT numScissorRects, D3D12_RECT* scissorRects) noexcept
{
	//assert(numRects < MAX_SCISSORRECT);
	//assert(scissorRects);

	constexpr UINT maxSize = sizeof(D3D12_RECT) * MAX_SCISSORRECT;

	m_state.m_numScissorRects = numScissorRects;
	memcpy_s(m_state.m_scissorRects.data(), maxSize, scissorRects, sizeof(D3D12_RECT) * numScissorRects);

	m_setScissorRects = true;
}

void D3D12StateCache::SetConstantBuffer(ShaderType shaderType, UINT index, D3D12ConstantBufferView* constantBufferView) noexcept
{
	//assert(index < MAX_CONSTANT_BUFFER_VIEW);
	//assert(constantBufferView);

	auto& views = m_state.m_cbvCache.views[shaderType];
	auto& indexMasks = m_state.m_cbvCache.indexMasks[shaderType];

	views[index] = constantBufferView;
	indexMasks |= (1 << (index + 1));
}

void D3D12StateCache::SetShaderResource(ShaderType shaderType, UINT index, D3D12ShaderResourceView* shaderResourceView) noexcept
{
	//assert(index < MAX_SHADER_RESOURCE_VIEW);
	//assert(shaderResourceView);

	auto& views = m_state.m_srvCache.views[shaderType];
	auto& indexMasks = m_state.m_srvCache.indexMasks[shaderType];

	views[index] = shaderResourceView;
	indexMasks |= (1 << (index + 1));
}

void D3D12StateCache::SetUnorderedAccess(ShaderType shaderType, UINT index, D3D12UnorderedAccessView* unorderedAccessView) noexcept
{
	//assert(index < MAX_UNORDERED_ACCESS_VIEW);
	//assert(unorderedAccessView);

	auto& views = m_state.m_uavCache.views[shaderType];
	auto& indexMasks = m_state.m_uavCache.indexMasks[shaderType];

	views[index] = unorderedAccessView;
	indexMasks |= (1 << (index + 1));
}

void D3D12StateCache::SetSampler(ShaderType shaderType, UINT index, D3D12Sampler* sampler) noexcept
{
	//assert(index < MAX_SAMPLER);
	//assert(sampler);

	auto& views = m_state.m_samplerCache.views[shaderType];
	auto& indexMasks = m_state.m_samplerCache.indexMasks[shaderType];

	views[index] = sampler;
	indexMasks |= (1 << index);

}

void D3D12StateCache::Flush() noexcept
{
	m_setPipelineState = false;
	m_setRootSignature = false;
	m_setVertexBuffer = false;
	m_setIndexBuffer = false;
	m_setPrimitiveTopology = false;
	m_setRenderTargets = false;
	m_setViewports = false;
	m_setScissorRects = false;
}