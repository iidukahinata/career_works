/**
* @file    D3D12DeviceChild.cpp
* @brief
*
* @date	   2022/08/01 2022îNìxèâî≈
*/


#include "D3D12DeviceChild.h"
#include "D3D12GrahicsDevice.h"
#include "D3D12Sampler.h"

ID3D12Device* D3D12DeviceChild::GetDevice() const noexcept
{
	return D3D12GrahicsDevice::Get().Device();
}

D3D12CommandContext* D3D12DeviceChild::GetCommandContext() const noexcept
{
	return 	&D3D12GrahicsDevice::Get().CommandContext();
}

D3D12DescriptorAllocator& D3D12DeviceChild::GetViewDescriptorAllocator() noexcept
{
	return 	D3D12GrahicsDevice::Get().ViewDescriptorAllocator();
}

D3D12DescriptorAllocator& D3D12DeviceChild::GetSamplerDescriptorAllocator() noexcept
{
	return 	D3D12GrahicsDevice::Get().SamplerDescriptorAllocator();
}

D3D12DescriptorAllocator& D3D12DeviceChild::GetRtvDescriptorAllocator() noexcept
{
	return 	D3D12GrahicsDevice::Get().RtvDescriptorAllocator();
}

D3D12DescriptorAllocator& D3D12DeviceChild::GetDsvDescriptorAllocator() noexcept
{
	return 	D3D12GrahicsDevice::Get().DsvDescriptorAllocator();
}

D3D12Map<D3D12_SAMPLER_DESC, D3D12Sampler*>& D3D12DeviceChild::GetSamplerMap() noexcept
{
	return 	D3D12GrahicsDevice::Get().GetSamplerMap();
}