/**
* @file    TitlePlayer.h
* @brief
*
* @date	   2022/06/09 2022îNìxèâî≈
* @author  î—íÀózëæ
*/
#pragma once


#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"
#include "../Component/Animator.h"
#include "SubSystem/Audio/AudioSpeaker.h"
#include "SubSystem/Resource/Resources/Audio/AudioClip.h"


class TitlePlayer : public IGameObject
{
public:
	
	// IGameObject
	void Awake() override;
	void Init() override;
	void Update() override;
	void Draw() override;

	const char* GetName() override;

	void StartScreenOutAnim() noexcept;

private:

	/* Animation function */
	void ScreenInAnim() noexcept;
	void ScreenOutAnim() noexcept;
	void RotationAnim() noexcept;

private:

	Model m_model;

	Animator m_animator;

	AudioSpeaker m_audioSpeaker;

	AudioClip* m_audioClip = nullptr;

	float m_speed = 10.f;

	class TitleString* m_titleString = nullptr;
};