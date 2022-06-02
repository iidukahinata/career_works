/**
* @file    Message.h
* @brief
*
* @date	   2022/06/02 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
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

	bool isDraw = false;

	// * stage ‚©‚ç map î•ñ‚ğæ“¾‚·‚é‚½‚ßB
	class Stage* m_stage = nullptr;

	Sprite m_sprite;
};