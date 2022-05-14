/**
* @file	   RenderStates.h
* @brief
*
* @date	   2022/04/22 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include <d3d11.h>
#include <wrl/client.h>

class RenderStates
{
public:

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