/**
* @file    Human.h
* @brief
*
* @date	   2022/06/03 2022îNìxèâî≈
* @author  î—íÀózëæ
*/
#pragma once


#include "IMass.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"

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

	void RotationWorld(const Math::Vector3& angle) noexcept;

private:

	const float m_maxSizeY = 1.2f;
	const float m_minSizeY = 0.8f;

	float m_animSpeed = 0.03f;

	Model m_model;
};