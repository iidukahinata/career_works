/**
* @file    D3D12DeviceChild.cpp
* @brief
*
* @date	   2022/05/13 2022îNìxèâî≈
* @author  î—íÀózëæ
*/


#include "D3D12DeviceChild.h"
#include "D3D12GrahicsDevice.h"

D3D12DeviceChild::D3D12DeviceChild()
{
	m_grahicsDevice = &D3D12GrahicsDevice::Get();
}

D3D12GrahicsDevice* D3D12DeviceChild::GetGraphicsDevice() const noexcept
{
	return m_grahicsDevice;
}