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

	void AnimUpdate() noexcept;

private:

	const Math::Vector2 aspect = Math::Vector2(3.2f, 2.4f);

	const float m_maxSize = 0.3f;
	const float m_minSize = 0.f;

	float m_nowSize = 0.f;

	float m_animSpeed = 0.f;

	bool m_isDraw = false;
	bool m_isAnim = false;

	// * stage ���� map �����擾���邽�߁B
	class Stage* m_stage = nullptr;

	Sprite m_sprite;
};