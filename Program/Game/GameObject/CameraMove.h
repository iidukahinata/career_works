/**
* @file    CameraMove.h
* @brief
*
* @date	   2022/05/28 2022�N�x����
* @author  �ђ˗z��
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

	// * player �𒆐S�ɉ�]���邽�߁B
	IGameObject* player = nullptr;

	// * 1 �̏ꍇ�A90 �t���[���ŉ�]�I��
	int m_rotateSpeed = 1;
	int m_rotateCount = 0;
};