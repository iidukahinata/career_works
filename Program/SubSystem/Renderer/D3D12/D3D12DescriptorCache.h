/**
* @file    D3D12DescriptorCache.h
* @brief
*
* @date	   2022/08/01 2022�N�x����
*/
#pragma once


#include "D3D12Helper.h"
#include "D3D12View.h"
#include "D3D12Sampler.h"
#include "D3D12DeviceChild.h"
#include "D3D12DescriptorAllocator.h"

class D3D12RootSignature;
struct ConstantBufferViewCache;
struct ShaderResourceViewCache;
struct UnorderedAccessViewCache;
struct SamplerCache;

/** SamplerCache �Ŏg�p���ꂽSampler�\����ێ����A�����o�^�����邽�ߍ쐬�B*/
struct SamplerArrayDesc
{
	UINT m_ids[MAX_SAMPLER];
};

/** Smapler �� Descriptor ��2048�����Ȃ����ߓ����ݒ���g���񂷂���Map�ɓo�^ */
typedef D3D12Map<SamplerArrayDesc, D3D12_GPU_DESCRIPTOR_HANDLE> D3D12SamplerMap;

class D3D12DescriptorCache : public D3D12DeviceChild
{
public:

	void Create() noexcept;
	void BegineFrame() noexcept;

	void SetDescriptorHeap() noexcept;
	void SetRenderTargets(UINT numRenderTargets, D3D12RenderTextureView** renderTargets, D3D12DepthStencilView* depthStencil) noexcept;
	void SetConstantBufferView(ShaderType type, ConstantBufferViewCache& cache, D3D12RootSignature* rootSignature) noexcept;
	void SetShaderResourceView(ShaderType type, ShaderResourceViewCache& cache, D3D12RootSignature* rootSignature) noexcept;
	void SetUnorderedAccessView(ShaderType type, UnorderedAccessViewCache& cache, D3D12RootSignature* rootSignature) noexcept;
	void SetSampler(ShaderType type, SamplerCache& cache, D3D12RootSignature* rootSignature) noexcept;

private:

	D3D12GlobalDescriptorHeap m_globalDescriptprHeap;
	D3D12GlobalAllocatedDescriptorHeap m_globalAllocatedDescriptprHeap;
	D3D12GlobalSamplerDescriptorHeap m_globalSamplerDescriptprHeap;

	// * null objects
	D3D12Descriptor* nullRenderTarget;
	D3D12Descriptor* nullConstantBuffer;
	D3D12Descriptor* nullShaderResource;
	D3D12Descriptor* nullUnorderedAccess;
	D3D12Descriptor* nullSampler;

	D3D12SamplerMap m_samplerMap;
};