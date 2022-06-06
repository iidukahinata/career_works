/**
* @file    D3D11ConstantBuffer.h
* @brief   
*
* @date	   2022/06/06 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "D3D11DeviceChild.h"
#include "SubSystem/Log/DebugLog.h"
#include "SubSystem/Tools/Tools.h"

template<class T>
class D3D11ConstantBuffer : public D3D11DeviceChild
{
public:

	/**
	* CPU側からの更新が多いと予測し動的リソースとして作成される。
	* @param bufferSize [入力] 16倍数ビットではない値でも可能です。
	*/
	bool Create(UINT bufferSize) noexcept;

	/** GPU データを更新します。 */
	void Update(const T& buffer) noexcept;

	/** デバイス設定するための関数です。*/
	void VSSet(UINT slot) noexcept;
	void PSSet(UINT slot) noexcept;

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

	HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		LOG_ERROR("コンスタントバッファー作成失敗 : D3D11ConstantBuffer.cpp");
		return false;
	}
	return true;
}

template<class T>
inline void D3D11ConstantBuffer<T>::Update(const T& buffer) noexcept
{
	auto context = GetGraphicsDevice()->GetContext();

	D3D11_MAPPED_SUBRESOURCE pData;
	HRESULT hr = context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr))
	{
		memcpy_s(pData.pData, pData.RowPitch, &buffer, sizeof(buffer));
		context->Unmap(m_constantBuffer.Get(), 0);
	}
}

template<class T>
inline void D3D11ConstantBuffer<T>::VSSet(UINT slot) noexcept
{
	GetGraphicsDevice()->GetContext()->VSSetConstantBuffers(slot, 1, m_constantBuffer.GetAddressOf());
}

template<class T>
inline void D3D11ConstantBuffer<T>::PSSet(UINT slot) noexcept
{
	GetGraphicsDevice()->GetContext()->PSSetConstantBuffers(slot, 1, m_constantBuffer.GetAddressOf());
}