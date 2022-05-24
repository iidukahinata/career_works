#pragma once


#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"

class Player : public IGameObject
{
public:

	// IGameObject
	void Init() override;
	void Update() override;
	void Draw() override;

private:

	void InputAction() noexcept;

	void Rolling() noexcept;
	void Move1Mass() noexcept;
	void Rotation90Degree() noexcept;

	void RotationWorld(const Math::Vector3& angle) noexcept;

	void FinishRotate() noexcept;

	int InputNum() const noexcept;
	bool IsInput() const noexcept;

private:

	static const int AngleSize = 2;
	int m_angles[AngleSize] = {};

	int m_angleCount;

	Model m_model;
};