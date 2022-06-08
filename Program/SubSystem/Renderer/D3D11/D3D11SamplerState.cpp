/**
* @file    D3D11SamplerState.cpp
* @brief
*
* @date	   2022/04/29 2022年度初版
* @author  飯塚陽太
*/


#include "D3D11SamplerState.h"
#include "SubSystem/Log/DebugLog.h"
#include "SubSystem/Tools/Tools.h"

bool D3D11SamplerState::Create(
	D3D11_FILTER filter /* = D3D11_FILTER_MIN_MAG_MIP_LINEAR */,
	D3D11_TEXTURE_ADDRESS_MODE addressU /* = D3D11_TEXTURE_ADDRESS_CLAMP */,
	D3D11_TEXTURE_ADDRESS_MODE addressV /* = D3D11_TEXTURE_ADDRESS_CLAMP */,
	D3D11_TEXTURE_ADDRESS_MODE addressW /* = D3D11_TEXTURE_ADDRESS_CLAMP */
) noexcept
{
	// テクスチャ・サンプラーの作成
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerDesc.Filter = filter;
	samplerDesc.AddressU = addressU;
	samplerDesc.AddressV = addressV;
	samplerDesc.AddressW = addressW;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT hr = GetGraphicsDevice()->GetDevice()->CreateSamplerState(&samplerDesc, m_sampler.GetAddressOf());
	if (FAILED(hr))
	{
		LOG_ERROR("サンプラー作成に失敗。");
		return false;
	}
	return true;
}

void D3D11SamplerState::PSSet(UINT slot /* =  0 */)
{
	GetGraphicsDevice()->GetContext()->PSSetSamplers(slot, 1, m_sampler.GetAddressOf());
}