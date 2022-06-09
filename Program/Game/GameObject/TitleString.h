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
#include "../Component/Animator.h"

class TitleString : public IGameObject
{
public:

	// IGameObject
	void Init() override;
	void Update() override;
	void Draw() override;

	const char* GetName() override;

	void StartUpDownAnim() noexcept;
	void StartFadeOutAnim() noexcept;

	bool IsNoneAnim() const noexcept;

private:

	void SetColor(const Math::Vector4& color) noexcept;

	/* Animation function */
	void OpneAnim() noexcept;
	void UpDownAnim() noexcept;
	void FadeOutAnim() noexcept;
	void StopTitleAnim() noexcept;

private:

	Sprite m_sprite;

	Animator m_animator;

	struct ConstantBufferColor
	{
		Math::Vector4 m_color;
	};

	D3D11ConstantBuffer<ConstantBufferColor> m_constantBuffer;

	float m_addSpeed = 0.f;
	float m_speed = 0.f;
};