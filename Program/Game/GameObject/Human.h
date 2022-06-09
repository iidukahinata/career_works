/**
* @file    Human.h
* @brief
*
* @date	   2022/06/09 2022îNìxèâî≈
* @author  î—íÀózëæ
*/
#pragma once


#include "IMass.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"
#include "../Component/Animator.h"

class Human : public IMass
{
public:

	// IMass
	void Awake() override;
	void Init() override;
	void Update() override;
	void Draw() override;

	MassType GetType() override;

private:

	/* Animation function */
	void RotationAnim() noexcept;
	void RotationWorld(const Math::Vector3& angle) noexcept;

private:

	Model m_model;

	Animator m_animator;

	float m_animSpeed = 0.03f;
};