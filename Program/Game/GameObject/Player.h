/**
* @file    IMass.h
* @brief
*
* @date	   2022/06/09 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "IMass.h"
#include "../Component/HitStop.h"
#include "../Component/Animator.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"

enum BOX_FACE_INFO
{
	POSITIVE_X,
	POSITIVE_Y,
	POSITIVE_Z,
	NEGATIVE_X,
	NEGATIVE_Y,
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

	bool IsGameOver() const noexcept;
	bool IsGameClear() const noexcept;

private:

	void InputAction() noexcept;

	void Rolling() noexcept;
	void Move1Mass() noexcept;
	void Rotation90Degree() noexcept;

	void ChackTheNextMassFromStage() noexcept;
	void ChackTheNextMassFromMap() noexcept;

	void HitHuman(IMass* hitMass) noexcept;
	void HitEnemy(IMass* hitMass) noexcept;

	void RotationWorld(const Math::Vector3& angle) noexcept;

	void FinishRolling() noexcept;

	BOX_FACE_INFO GetNowBottomSurface() noexcept;

	int InputNum() const noexcept;
	bool IsInput() const noexcept;

	/* Animation funciton */
	void GameClearAnim() noexcept;
	void GameOverAnim() noexcept;

private:

	Model m_model;

	HitStop m_hitStop;

	Animator m_animator;

	Math::Vector3i m_nextMassPos;

	//* Item ��ێ����Ă���ʂ�������
	bool isGetHuman[BOX_FACE_INFO::Max];

	Math::Vector2 m_angle;

	int m_angleCount = 0;

	// * ���̒l��������Ɖ�]���x���オ��BangleCount �ƍ��킹�邽�� int ���g�p�B
	int m_rotateSpeed = 6;

	// * stage ���� map �����擾���邽�߁B
	class Stage* m_stage = nullptr;

	// * �J�����̌�������ړ��������擾���邽�߁B
	class CameraMove* m_cameraMove = nullptr;
};