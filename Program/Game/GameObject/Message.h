/**
* @file    Message.h
* @brief
*
* @date	   2022/06/03 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "IMass.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"
#include "../Component/Animator.h"

class Message : public IMass
{
public:

	// IMass
	void Init() override;
	void Update() override;
	void Draw() override;

	MassType GetType() override;

	void MessegeSpriteInit(int id) noexcept;

	void SetDrawMode(bool isDraw) noexcept;

private:

	/* Animation function */
	void OpenAnim() noexcept;

private:

	Sprite m_sprite;

	Animator m_animator;

	const Math::Vector2 aspect = Math::Vector2(3.2f, 2.4f);

	float m_nowSize = 0.f;

	float m_animSpeed = 0.f;

	bool m_isDraw = false;

	// * stage ���� map �����擾���邽�߁B
	class Stage* m_stage = nullptr;
};