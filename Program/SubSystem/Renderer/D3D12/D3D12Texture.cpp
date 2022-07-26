/**
* @file    D3D12Texture.cpp
* @brief
*
* @date	   2022/07/26 2022îNìxèâî≈
*/


#include "D3D12Texture.h"
#include "D3D12GrahicsDevice.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

bool D3D12Texture::Create(DXGI_FORMAT format, UINT width)
{
	const auto texDesc = CD3DX12_RESOURCE_DESC::Tex1D(format, width);
	const auto texHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);

	return Create(texDesc, texHeapProp);
}

bool D3D12Texture::Create(DXGI_FORMAT format, UINT width, UINT height)
{
	const auto texDesc = CD3DX12_RESOURCE_DESC::Tex2D(format, width, height);
	const auto texHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);

	return Create(texDesc, texHeapProp);
}

bool D3D12Texture::Create(DXGI_FORMAT format, UINT width, UINT height, UINT depth)
{
	const auto texDesc = CD3DX12_RESOURCE_DESC::Tex3D(format, width, height, depth);
	const auto texHeapProp = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);

	return Create(texDesc, texHeapProp);
}

bool D3D12Texture::Create(D3D12_RESOURCE_DESC desc, D3D12_HEAP_PROPERTIES heapProp)
{
	auto hr = GetDevice()->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,
		nullptr,
		IID_PPV_ARGS(m_texture.ReleaseAndGetAddressOf()));

	if (FAILED(hr)) {
		return false;
	}

	return true;
}

bool D3D12Texture::Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta)
{
	auto hr = DirectX::CreateTexture(GetDevice(), meta, m_texture.ReleaseAndGetAddressOf());

	if (FAILED(hr)) {
		LOG_ERROR("ShaderResourceView ÇÃê∂ê¨Ç…é∏îsÇµÇ‹ÇµÇΩÅB");
		return false;
	}
	return true;
}

void D3D12Texture::SetResource(ID3D12Resource* resource)
{
	m_texture = resource;
}