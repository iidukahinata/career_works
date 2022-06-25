/**
* @file    ID3D11InputLayout.cpp
* @brief
*
* @date	   2022/04/29 2022年度初版
* @author  飯塚陽太
*/


#include "D3D11InputLayout.h"
#include "SubSystem/Log/DebugLog.h"
#include "SubSystem/Core/Common/Common.h"

bool D3D11InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* layout, UINT layoutSize, ID3DBlob* blob) noexcept
{
	if (!layout) {
		LOG_ERROR("layoutを指定してください。");
		return false;
	}

	if (!blob) {
		LOG_ERROR("blobに値をいれてください。");
		return false;
	}

	//頂点レイアウト作成
	HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateInputLayout(
		layout,
		layoutSize,
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		m_inputLayout.GetAddressOf());

	if (FAILED(hr)) {
		LOG_ERROR("InputLayout作成に失敗。");
		return false;
	}

	return true;
}

void D3D11InputLayout::IASet() noexcept
{
	GetGraphicsDevice()->GetContext()->IASetInputLayout(m_inputLayout.Get());
}