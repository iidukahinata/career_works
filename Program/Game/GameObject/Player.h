/**
* @file    Player.h
* @brief
*
* @date	   2022/05/28 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "IMass.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"

class Player : public IMass
{
public:

	// IMass
	void Awake() override;
	void Init() override;
	void Update() override;
	void Draw() override;

	const char* GetName() override;

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

	int m_angleCount = 0;

	// * stage から map 情報を取得するため。
	class Stage* m_stage = nullptr;

	// * この値が増えると回転速度が上がる。angleCount と合わせるため int を使用。
	int m_rotateSpeed = 6;

	Model m_model;
};