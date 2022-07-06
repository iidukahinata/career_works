/**
* @file	   RenderStates.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include <d3d11.h>
#include <wrl/client.h>

class D3D11RenderStates
{
	D3D11RenderStates() = default;
	COPY_PROHIBITED(D3D11RenderStates);
public:

	static D3D11RenderStates& Get() noexcept
	{
		static D3D11RenderStates instance;
		return instance;
	}

	bool Init();

	void SetBlendState(ID3D11BlendState* blendState);
	void SetRasterizerState(ID3D11RasterizerState* rasterizer);

public:

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_noCull;					// �J�����O�Ȃ�
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_cullClockWise;			// �J�����O����
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_wireframeCull;			// ���C���[�t���[��
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_depthTiltBias;			// �[�x�X�΃o�C�A�X

	Microsoft::WRL::ComPtr<ID3D11BlendState> m_noAlphaBlend;				// �A���t�@�u�����h�Ȃ�
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_alphaEnabledBlend;			// �A���t�@�u�����h����
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_additiveBlend;				// ���Z
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_additiveTransparencyBlend;	// ���Z(����)
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_subtractionBlend;			// ���Z
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_multiplicationBlend;			// ��Z
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_screenCompositingBlend;		// �X�N���[��
};