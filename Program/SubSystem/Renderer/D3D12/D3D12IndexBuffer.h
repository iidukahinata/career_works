/**
* @file    D3D12IndexBuffer.h
* @brief
*
* @date	   2022/07/06 2022年度初版
* @note
*	このクラスでは unsigned short型には対応していない
*/
#pragma once


#include <vector>
#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12IndexBuffer : public D3D12DeviceChild
{
public:

	bool Create(const Vector<UINT>& indices) noexcept;
	void Update(const Vector<UINT>& indices) noexcept;
	void IASet() noexcept;

	ID3D12Resource*          Get() const noexcept { return m_buffer.Get(); };
	D3D12_INDEX_BUFFER_VIEW& GetView() noexcept { return m_bufferView; };

private:

	Microsoft::WRL::ComPtr<ID3D12Resource> m_buffer;
	D3D12_INDEX_BUFFER_VIEW m_bufferView;

	UINT m_bytesSize;
};