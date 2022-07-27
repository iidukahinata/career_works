/**
* @file    D3D12DeviceChild.cpp
* @brief
*
* @date	   2022/07/26 2022îNìxèâî≈
*/


#include "D3D12DeviceChild.h"
#include "D3D12GrahicsDevice.h"

ID3D12Device* D3D12DeviceChild::GetDevice() const noexcept
{
	return D3D12GraphicsDevice::Get().GetDevice();
}

ID3D12GraphicsCommandList* D3D12DeviceChild::GetCommandList() const noexcept
{
	return 	D3D12GraphicsDevice::Get().GetCommandList();
}