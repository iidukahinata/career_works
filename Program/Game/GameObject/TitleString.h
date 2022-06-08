/**
* @file    TitleString.h
* @brief
*
* @date	   2022/06/08 2022îNìxèâî≈
* @author  î—íÀózëæ
*/
#pragma once


#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"
#include "SubSystem/Renderer/D3D11/D3D11ConstantBuffer.h"

class TitleString : public IGameObject
{
public:

	enum class AnimMode
	{
		Opne,
		UpDown,
		FadeOut,
		None,
	};

	// IGameObject
	void Init() override;
	void Update() override;
	void Draw() override;

	const char* GetName() override;

	AnimMode GetAnimMode() const noexcept;

	void StartUpDownAnim() noexcept;
	void StartFadeOutAnim() noexcept;

private:

	void OpneAnimUpdate() noexcept;
	void UpDownAnimUpdate() noexcept;
	void FadeOutAnimUpdate() noexcept;

	void StopTitleAnim() noexcept;

	void SetColor(const Math::Vector4& color) noexcept;

private:

	Sprite m_sprite;

	struct ConstantBufferColor
	{
		Math::Vector4 m_color;
	};

	D3D11ConstantBuffer<ConstantBufferColor> m_constantBuffer;

	AnimMode m_animMode = AnimMode::Opne;

	float m_addSpeed = 0.f;
	float m_speed = 0.f;
};