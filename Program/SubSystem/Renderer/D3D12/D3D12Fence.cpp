/**
* @file    D3D12Fence.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
*/


#include "D3D12CommandContext.h"
#include "D3D12GrahicsDevice.h"

D3D12Fence::~D3D12Fence()
{
	CloseHandle(m_fenceEvent);
}

bool D3D12Fence::Create() noexcept
{
	HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateFence(
		0,
		D3D12_FENCE_FLAG_NONE,
		IID_PPV_ARGS(m_fence.ReleaseAndGetAddressOf()));

	if (FAILED(hr))
	{
		return false;
	}

	m_fenceValue = 1;

	m_fenceEvent = CreateEvent(nullptr, false, false, nullptr);
	if (!m_fenceEvent)
	{
		return false;
	}
	return true;
}

void D3D12Fence::WaitForSingleToFinish() noexcept
{
	if (m_fence->GetCompletedValue() < m_fenceValue)
	{
		m_fence->SetEventOnCompletion(m_fenceValue, m_fenceEvent);
		WaitForSingleObject(m_fenceEvent, INFINITE);

		// 次のフレームのフェンス値に更新
		m_fenceValue++;
	}
}