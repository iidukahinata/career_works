/**
* @file    D3D12Buffer.h
* @brief
*
* @date	   2022/07/30 2022年度初版
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"

class D3D12Buffer : public D3D12DeviceChild
{
public:

    /** アクセス */
    ID3D12Resource*     Get()          const noexcept { return m_buffer.Get(); }
    ID3D12Resource**    GetAddressOf()       noexcept { return m_buffer.GetAddressOf(); }
    D3D12_RESOURCE_DESC GetDesc()      const noexcept { return m_buffer->GetDesc(); }

protected:

	bool Create(
        const D3D12_HEAP_PROPERTIES* pHeapProperties,
        D3D12_HEAP_FLAGS HeapFlags,
        const D3D12_RESOURCE_DESC* pDesc,
        D3D12_RESOURCE_STATES InitialResourceState = D3D12_RESOURCE_STATE_GENERIC_READ,
        const D3D12_CLEAR_VALUE* pOptimizedClearValue = nullptr) noexcept;

    void UpdateBuffer(UINT destSize, void* srcPtr, UINT srcSize) noexcept;

protected:

    Microsoft::WRL::ComPtr<ID3D12Resource> m_buffer;
};