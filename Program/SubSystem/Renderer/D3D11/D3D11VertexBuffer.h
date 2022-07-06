/**
* @file    D3D11VertexBuffer.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include "D3D11DeviceChild.h"

template<class T>
class D3D11VertexBuffer : public D3D11DeviceChild
{
public:

	/**
	* @param indices [����] �������_�f�[�^
	* @param usage [����] D3D11_USAGE_DYNAMIC �ȊO�̒l�̏ꍇ�� D3D11_USAGE_DEFAULT �ɂȂ�܂��B
	*/
	bool Create(const Vector<T>& vertices, D3D11_USAGE usage = D3D11_USAGE_DEFAULT) noexcept;

	/** GPU �f�[�^���X�V���܂��B */
	void Update(const Vector<T>& vertices) const noexcept;

	/** �f�o�C�X�ݒ肷�邽�߂̊֐��ł��B*/
	void IASet(UINT slot = 0) const noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
};

template<class T>
inline bool D3D11VertexBuffer<T>::Create(const Vector<T>& vertices, D3D11_USAGE usage /* = D3D11_USAGE_DEFAULT */) noexcept
{
	// ���_�o�b�t�@�p��
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.ByteWidth = sizeof(T) * vertices.size();
	bufferDesc.Usage = (usage & D3D11_USAGE_DYNAMIC) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = (usage & D3D11_USAGE_DYNAMIC) ? D3D11_CPU_ACCESS_WRITE : 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = vertices.data();

	HRESULT hr = GetDevice()->CreateBuffer(&bufferDesc, &initData, m_vertexBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		LOG_ERROR("���_�o�b�t�@�[�쐬�Ɏ��s�B");
		return false;
	}
	return true;
}

template<class T>
inline void D3D11VertexBuffer<T>::Update(const Vector<T>& vertices) const noexcept
{
	D3D11_MAPPED_SUBRESOURCE pData;
	HRESULT hr = GetContext()->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr))
	{
		memcpy_s(pData.pData, pData.RowPitch, vertices.data(), sizeof(T) * vertices.size());
		GetContext()->Unmap(m_vertexBuffer.Get(), 0);
	}
}

template<class T>
inline void D3D11VertexBuffer<T>::IASet(UINT slot /* = 0 */) const noexcept
{
	const UINT stride = sizeof(T);
	const UINT offset = 0;
	GetContext()->IASetVertexBuffers(slot, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
}