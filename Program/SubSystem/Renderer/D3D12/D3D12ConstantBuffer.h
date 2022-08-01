/**
* @file    D3D12ConstantBuffer.h
* @brief
*
* @date	   2022/08/01 2022�N�x����
*/
#pragma once


#include "D3D12View.h"
#include "D3D12Buffer.h"

class D3D12ConstantBuffer : public D3D12Buffer
{
public:

	bool Create(UINT bufferSize) noexcept;

	template<class T>
	void Update(const T& buffer) noexcept;

	void VSSet(UINT slot = 0) noexcept;
	void PSSet(UINT slot = 0) noexcept;
	void GSSet(UINT slot = 0) noexcept;

	/** �A�N�Z�X */
	HANDLE GetCPUData() const noexcept { return m_constantBufferCPU; }
	D3D12ConstantBufferView& GetView() noexcept { return m_view; }

private:

	// * CPU�チ�����̃o�b�t�@�擪�A�h���X
	HANDLE m_constantBufferCPU;

	D3D12ConstantBufferView m_view;
};

template<class T>
FORCEINLINE void D3D12ConstantBuffer::Update(const T& buffer) noexcept
{
	memcpy_s(m_constantBufferCPU, m_view.GetDesc().SizeInBytes, &buffer, sizeof(buffer));
}