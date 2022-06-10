/**
* @file    UIText.h
* @brief
*
* @date	   2022/06/10 2022îNìxèâî≈
* @author  î—íÀózëæ
*/
#pragma once


#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"
#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"

class TextUI : public IGameObject
{
public:

	// IGameObject
	void Init() override;
	void Draw() override;

	void SpriteInit(std::string_view name) noexcept;

	void SetIsDraw(bool isDraw) noexcept;
	void ChangeColor() noexcept;

private:

	Sprite m_sprite;

	struct ConstantBufferColor
	{
		Math::Vector4 m_color;
	};

	D3D11ConstantBuffer<ConstantBufferColor> m_constatBuffer;

	bool m_isDraw = true;
};

class TextUIManager : public IGameObject
{
public:

	// IGameObject
	void Awake() override;
	void Init() override;
	void Draw() override;

private:

	void TitleUIInit();
	void SelectUIInit();
	void GameUIInit();

private:

	std::vector<TextUI> m_texts;
};