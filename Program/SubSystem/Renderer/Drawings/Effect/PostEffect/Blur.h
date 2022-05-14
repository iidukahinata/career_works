/**
* @file	   Blur.h
* @brief
*
* @date	   2022/05/11 2022�N�x����
* @author  �ђ˗z��
* @note
*  �K�E�V�A���u���[�ł̃u���[��������
*/
#pragma once


#include "PostEffect.h"
#include "SubSystem/Renderer/D3D11/D3D11RenderTexture.h"
#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"

class Blur : public PostEffect
{
public:

	bool Init(Texture* texture) override;
	bool Init(Texture* texture, const Math::Vector2& textureSize);

	void Draw() override;

	Texture* GetTexture() override;

	void SetVariance(float variance);

private:

	void CreateRenderTextures(const Math::Vector2& textureSize);
	void CreateSprites(Texture* texture);

	void CalculateWeightTablesFromGaussian(float variance);

private:

	// * ���u���[�������s��
	Sprite m_xBlurSprite;

	// * �c�u���[�������s��
	Sprite m_yBlurSprite;

	D3D11RenderTexture m_xBlurRenderTexture;
	D3D11RenderTexture m_yBlurRenderTexture;

	// �K�E�V�A���u���[�̏d��
	float m_weights[8];

	struct ConstantBufferBlur
	{
		float weights[8];
		Math::Vector2 screenSize;
	};

	D3D11ConstantBuffer<ConstantBufferBlur> m_constantBuffer;
};