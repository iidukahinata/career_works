/**
* @file    D3D11ConstantBuffer.h
* @brief   
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "D3D11DeviceChild.h"

template<class T>
class D3D11ConstantBuffer : public D3D11DeviceChild
{
public:

	/**
	* CPU������̍X�V�������Ɨ\�������I���\�[�X�Ƃ��č쐬�����B
	* @param bufferSize [����] 16�{���r�b�g�ł͂Ȃ��l�ł��\�ł��B
	*/
	bool Create(UINT bufferSize) noexcept;

	/** GPU �f�[�^���X�V���܂��B */
	void Update(const T& buffer) noexcept;

	/** �f�o�C�X�ݒ肷�邽�߂̊֐��ł��B*/
	void VSSet(UINT slot) const noexcept;
	void PSSet(UINT slot) const noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
};

template<class T>
inline bool D3D11ConstantBuffer<T>::Create(UINT bufferSize) noexcept
{
	int adjustBufferSize = AdjustToMultiples(bufferSize, 16);

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = adjustBufferSize;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	HRESULT hr = GetDevice()->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		LOG_ERROR("�R���X�^���g�o�b�t�@�[�쐬�Ɏ��s�B");
		return false;
	}
	return true;
}

template<class T>
inline void D3D11ConstantBuffer<T>::Update(const T& buffer) noexcept
{
	D3D11_MAPPED_SUBRESOURCE pData;
	HRESULT hr = GetContext()->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr))
	{
		memcpy_s(pData.pData, pData.RowPitch, &buffer, sizeof(buffer));
		GetContext()->Unmap(m_constantBuffer.Get(), 0);
	}
}

template<class T>
inline void D3D11ConstantBuffer<T>::VSSet(UINT slot) const noexcept
{
	GetContext()->VSSetConstantBuffers(slot, 1, m_constantBuffer.GetAddressOf());
}

template<class T>
inline void D3D11ConstantBuffer<T>::PSSet(UINT slot) const noexcept
{
	GetContext()->PSSetConstantBuffers(slot, 1, m_constantBuffer.GetAddressOf());
}