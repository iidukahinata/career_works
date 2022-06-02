/**
* @file    IMass.h
* @brief
*
* @date	   2022/06/01 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "IMass.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"

enum BOX_FACE_INFO
{
	POSITIVE_X,
	NEGATIVE_X,
	POSITIVE_Y,
	NEGATIVE_Y,
	POSITIVE_Z,
	NEGATIVE_Z,
	Max
};

class Player : public IMass
{
public:

	// IMass
	void Awake() override;
	void Init() override;
	void Update() override;
	void Draw() override;

	const char* GetName() override;

	MassType GetType() override;

private:

	void InputAction() noexcept;

	void Rolling() noexcept;
	void Move1Mass() noexcept;
	void Rotation90Degree() noexcept;

	void ChackTheNextMassFromStage() noexcept;
	void ChackTheNextMassFromMap() noexcept;

	void HitItem(IMass* hitMass) noexcept;
	void HitMessege(IMass* hitMass) noexcept;
	void HitEnemy(IMass* hitMass) noexcept;

	void RotationWorld(const Math::Vector3& angle) noexcept;

	void FinishRolling() noexcept;

	BOX_FACE_INFO GetNowBottomSurface() noexcept;

	int InputNum() const noexcept;
	bool IsInput() const noexcept;

private:

	Math::Vector3i m_nextMassPos;

	Math::Vector2 m_angle;

	//* Item ��ێ����Ă���ʂ�������
	bool isGetItem[BOX_FACE_INFO::Max];

	int m_angleCount = 0;

	// * stage ���� map �����擾���邽�߁B
	class Stage* m_stage = nullptr;

	// * �J�����̌�������ړ��������擾���邽�߁B
	class CameraMove* m_cameraMove = nullptr;

	// * ���̒l��������Ɖ�]���x���オ��BangleCount �ƍ��킹�邽�� int ���g�p�B
	int m_rotateSpeed = 6;

	Model m_model;
};