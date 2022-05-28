/**
* @file    CameraMove.h
* @brief
*
* @date	   2022/05/28 2022年度初版
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

private:

	void RotationY90Degree() noexcept;
	void FinishRotation() noexcept;

private:

	// * player を中心に回転するため。
	IGameObject* player = nullptr;

	// * 1 の場合、90 フレームで回転終了
	int m_rotateSpeed = 1;
	int m_rotateCount = 0;
};