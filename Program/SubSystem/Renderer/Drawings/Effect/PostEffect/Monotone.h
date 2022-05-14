/**
* @file	   Monotone.h
* @brief
*
* @date	   2022/05/11 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/
#pragma once


#include "PostEffect.h"
#include "SubSystem/Renderer/D3D11/D3D11RenderTexture.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"

class Monotone : public PostEffect
{
public:

	bool Init(Texture* texture) override;
	void Draw() override;

	Texture* GetTexture() override;

private:

	Sprite m_sprite;

	D3D11RenderTexture m_renderTexture;
};