/**
* @file    D3D12ConstantBuffer.h
* @brief
*
* @date	   2022/07/26 2022îNìxèâî≈
*/
#pragma once


#include "D3D12DeviceChild.h"
#include "D3D12GrahicsDevice.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

class D3D12ConstantBuffer : public D3D12DeviceChild
{
public:

	bool Create(UINT bufferSize, UINT count = 1) noexcept;

	template<class T>
	void Update(const T& buffer) noexcept;

	template<class T = void*>
	T GetCPUData() const noexcept;
	D3D12_CONSTANT_BUFFER_VIEW_DESC GetDesc() const noexcept;

	ID3D12Resource* Get() const noexcept { return m_constantBuffer.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D12Resource> m_constantBuffer;
	HANDLE m_constantBufferCPU;
	UINT m_adjustBufferSize;
};

template<class T>
FORCEINLINE void D3D12ConstantBuffer::Update(const T& buffer) noexcept
{
	memcpy_s(m_constantBufferCPU, m_adjustBufferSize, &buffer, sizeof(buffer));
}

template<class T /* = void* */>
FORCEINLINE T D3D12ConstantBuffer::GetCPUData() const noexcept
{
	return static_cast<T>(m_constantBufferCPU);
}