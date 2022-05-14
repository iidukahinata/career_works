/**
* @file    ID3D11InputLayout.h
* @brief
*
* @date	   2022/04/29 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include <wrl/client.h>
#include "D3D11DeviceChild.h"

class D3D11InputLayout : public D3D11DeviceChild
{
public:

	/**
	* @param layout [入力] レイアウト配列の先頭ポインタを指定してください。
	* @param layoutSize [入力] レイアウト配列サイズを指定してください。
	* @param blobs [入力] 頂点シェーダーのコンパイルデータを指定してください。
	*/
	bool Create(D3D11_INPUT_ELEMENT_DESC* layout, UINT layoutSize, ID3DBlob* blob) noexcept;

	/** デバイス設定するための関数です。*/
	void IASet() noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
};