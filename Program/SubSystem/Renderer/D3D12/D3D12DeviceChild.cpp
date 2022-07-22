/**
* @file    D3D12DeviceChild.cpp
* @brief
*
* @date	   2022/07/22 2022îNìxèâî≈
*/


#include "D3D12DeviceChild.h"
#include "D3D12GrahicsDevice.h"

ID3D12Device* D3D12DeviceChild::GetDevice() noexcept
{
	return D3D12GraphicsDevice::Get().GetDevice();
}

D3D12CommandContext* D3D12DeviceChild::GetContext() noexcept
{
	return &D3D12GraphicsDevice::Get().GetCommandContext();
}
