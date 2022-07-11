/**
* @file	   RenderStates.cpp
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/


#include "RenderStates.h"
#include "D3D11GrahicsDevice.h"

bool D3D11RenderStates::Init()
{
	auto device = D3D11GraphicsDevice::Get().GetDevice();
	auto context = D3D11GraphicsDevice::Get().GetContext();

	HRESULT  hr;

	// �u�����h�X�e�[�g����
	{
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		// �A���t�@�u�����h�Ȃ�
		blendDesc.RenderTarget[0].BlendEnable = false;
		hr = device->CreateBlendState(&blendDesc, m_noAlphaBlend.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}

		// �A���t�@�u�����h����
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		hr = device->CreateBlendState(&blendDesc, m_alphaEnabledBlend.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}

		// ���Z
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		hr = device->CreateBlendState(&blendDesc, m_additiveBlend.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}

		// ���Z(����)
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		hr = device->CreateBlendState(&blendDesc, m_additiveTransparencyBlend.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}

		// ���Z
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
		hr = device->CreateBlendState(&blendDesc, m_subtractionBlend.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}

		// ��Z
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
		hr = device->CreateBlendState(&blendDesc, m_multiplicationBlend.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}

		// �X�N���[��
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_INV_DEST_COLOR;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		hr = device->CreateBlendState(&blendDesc, m_screenCompositingBlend.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}
	}

	// ���X�^���C�Y����
	{
		D3D11_RASTERIZER_DESC rasterDesc;
		ZeroMemory(&rasterDesc, sizeof(rasterDesc));
		rasterDesc.DepthClipEnable = true;

		// ���C���[�t���[��
		rasterDesc.FillMode = D3D11_FILL_WIREFRAME;
		rasterDesc.CullMode = D3D11_CULL_NONE;
		hr = device->CreateRasterizerState(&rasterDesc, m_wireframeCull.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}

		// �J�����O�Ȃ�
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.CullMode = D3D11_CULL_NONE;
		hr = device->CreateRasterizerState(&rasterDesc, m_noCull.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}

		// �J�����O����
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.FrontCounterClockwise = true;
		hr = device->CreateRasterizerState(&rasterDesc, m_cullClockWise.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}

		// �[�x�X�΃o�C�A�X
		rasterDesc.CullMode = D3D11_CULL_BACK;
		rasterDesc.FrontCounterClockwise = false;
		rasterDesc.DepthBias = 100000;
		rasterDesc.SlopeScaledDepthBias = 1.0f;
		hr = device->CreateRasterizerState(&rasterDesc, m_depthTiltBias.GetAddressOf());
		if (FAILED(hr)) {
			return false;
		}
	}

	// �A���t�@�u�����h�L��
	SetBlendState(m_alphaEnabledBlend.Get());

	//  �J�����O�Ȃ�
	SetRasterizerState(m_noCull.Get());
}

void D3D11RenderStates::SetBlendState(ID3D11BlendState* blendState)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	D3D11GraphicsDevice::Get().GetContext()->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}

void D3D11RenderStates::SetRasterizerState(ID3D11RasterizerState* rasterizerState)
{
	D3D11GraphicsDevice::Get().GetContext()->RSSetState(rasterizerState);
}