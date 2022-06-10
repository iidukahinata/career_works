/**
* @file    CameraMove.h
* @brief
*
* @date	   2022/06/10 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "SubSystem/Renderer/Camera/Camera.h"
#include "SubSystem/Scene/GameObject.h"

class CameraMove : public IGameObject
{
public:

	void Init() override;
	void Update() override;

	const char* GetName() override;

	Math::Vector2 GetDirection() noexcept;

private:

	void RotationY90Degree() noexcept;
	void FinishRotation() noexcept;

private:

	enum DIRECTION
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
	};

	DIRECTION m_directionID = DIRECTION::UP;

	// * 1 の場合、90 フレームで回転終了
	int m_rotateSpeed = 2;
	int m_rotateCount = 0;

	// * player を中心に回転するため。
	class Player* player = nullptr;
};