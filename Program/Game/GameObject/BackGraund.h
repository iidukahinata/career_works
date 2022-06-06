/**
* @file    BackGraund.h
* @brief
*
* @date	   2022/06/03 2022îNìxèâî≈
* @author  î—íÀózëæ
*/
#pragma once


#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"

class BackGraund : public IGameObject
{
public:

	// IGameObject
	void Init() override;
	void Update() override;
	void Draw() override;

private:

	void OpneAnimUpdate() noexcept;
	void UpAnimUpdate() noexcept;
	void DownAnimUpdate() noexcept;

private:

	enum AnimMode
	{
		Opne,
		Up,
		Down,
		None,
	};

	AnimMode m_animMode = AnimMode::Opne;

	float m_addSpeed = 0.f;
	float m_speed = 0.f;

	Sprite m_sprite;
};