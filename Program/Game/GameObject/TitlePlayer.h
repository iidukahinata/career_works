/**
* @file    TitlePlayer.h
* @brief
*
* @date	   2022/06/06 2022îNìxèâî≈
* @author  î—íÀózëæ
*/
#pragma once


#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"

class TitlePlayer : public IGameObject
{
public:

	enum class AnimMode
	{
		ScreenIn,
		Rotation,
		ScreenOut,
		None,
	};

	void Init() override;
	void Update() override;
	void Draw() override;

	const char* GetName() override;

	void StartScreenOutAnim() noexcept;

private:

	void ScreenInAnimUpdate() noexcept;
	void ScreenOutAnimUpdate() noexcept;
	void RotationAnimUpdate() noexcept;

private:

	class TitleString* m_titleString = nullptr;

	Model m_model;

	AnimMode m_animMode;
	float m_speed = 10.f;
};