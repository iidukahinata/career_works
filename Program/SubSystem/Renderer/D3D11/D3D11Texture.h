/**
* @file    D3D11Texture.h
* @brief
*
* @date	   2022/06/25 2022年度初版
*/
#pragma once


#include "D3D11DeviceChild.h"
#include "ThirdParty/directxtex/include/DirectXTex.h"

class D3D11Texture : public D3D11DeviceChild
{
public:

	/**
	* @param images [入力] イメージ配列の先頭ポインタを指定してください。
	* @param imageSize [入力] イメージ配列サイズを指定してください。
	* @param meta [入力] 読み込まれたテクスチャ meta データを指定してください。
	*/
	bool Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta);

	/** デバイス設定するための関数です。*/
	void PSSet(UINT slot = 0) const noexcept;

	void SetShaderResourceView(ID3D11ShaderResourceView* shaderResourceView) noexcept;

	/* アクセス */
	ID3D11ShaderResourceView* GetShaderResourceView() const noexcept;
	ID3D11ShaderResourceView** GetAddressOfShaderResourceView() noexcept;

private:
	
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;
};