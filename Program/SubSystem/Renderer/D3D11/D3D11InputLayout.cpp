/**
* @file    ID3D11InputLayout.cpp
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/


#include "D3D11InputLayout.h"

bool D3D11InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* layout, UINT layoutSize, ID3DBlob* blob) noexcept
{
	if (!layout) {
		LOG_ERROR("layout���w�肵�Ă��������B");
		return false;
	}

	if (!blob) {
		LOG_ERROR("blob�ɒl������Ă��������B");
		return false;
	}

	//���_���C�A�E�g�쐬
	HRESULT hr = GetDevice()->CreateInputLayout(
		layout,
		layoutSize,
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		m_inputLayout.ReleaseAndGetAddressOf());

	if (FAILED(hr)) {
		LOG_ERROR("InputLayout�쐬�Ɏ��s�B");
		return false;
	}

	return true;
}

void D3D11InputLayout::IASet() const noexcept
{
	GetContext()->IASetInputLayout(m_inputLayout.Get());
}