/**
* @file    D3D12Texture.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include <d3d12.h>
#include <wrl/client.h>
#include "D3D12DeviceChild.h"
#include "ThirdParty/directxtex/include/DirectXTex.h"

class D3D12Texture : public D3D12DeviceChild
{
public:

	/**
	* @param images [入力] イメージ配列の先頭ポインタを指定してください。
	* @param imageSize [入力] イメージ配列サイズを指定してください。
	* @param meta [入力] 読み込まれたテクスチャ meta データを指定してください。
	*/
	bool Create(const DirectX::Image* images, size_t imageSize, const DirectX::TexMetadata& meta);
	
	void SetResource(ID3D12Resource* resource);

	/* アクセス */
	ID3D12Resource* GetResource() const noexcept;
	ID3D12Resource** GetAddressOfResource() noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D12Resource> m_texture;
};