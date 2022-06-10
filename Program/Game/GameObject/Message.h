/**
* @file    Message.h
* @brief
*
* @date	   2022/06/09 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/
#pragma once


#include "IMass.h"
#include "../Component/Animator.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"

class Message : public IMass
{
public:

	// IMass
	void Awake() override;
	void Init() override;
	void Update() override;
	void Draw() override;

	MassType GetType() override;

	void MessegeSpriteInit(int id) noexcept;

	void SetDrawMode(bool isDraw) noexcept;

private:

	/* Animation function */
	void OpenAnim() noexcept;
	void CloseAnim() noexcept;

private:

	Sprite m_windowSprite;
	Sprite m_sprite;

	Animator m_animator;

	float m_nowSize = 0.f;

	bool m_isDraw = false;

	// * stage ‚©‚ç map î•ñ‚ğæ“¾‚·‚é‚½‚ßB
	class Stage* m_stage = nullptr;

	const Math::Vector2 aspect = Math::Vector2(3.2f, 2.4f);
};