/**
* @file    D3D11IndexBuffer.h
* @brief
*
* @date	   2022/06/25 2022年度初版
*/
#pragma once


#include "D3D11DeviceChild.h"

class D3D11IndexBuffer : public D3D11DeviceChild
{
public:

	/** 
	* @param indices [入力] 初期インデックスデータ
	* @param usage [入力] D3D11_USAGE_DYNAMIC 以外の値の場合は D3D11_USAGE_DEFAULT になります。
	*/
	bool Create(const std::vector<UINT>& indices, D3D11_USAGE usage = D3D11_USAGE_DEFAULT) noexcept;

	/** GPU データを更新します。 */
	void Update(const std::vector<UINT>& indices) noexcept;

	/** DXGI_FORMAT_R32_UINT でデバイス設定されます。*/
	void IASet() const noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;
};