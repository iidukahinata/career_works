/**
* @file    BackGraund.h
* @brief
*
* @date	   2022/06/03 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/
#pragma once


#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Resource/Resources/2DSprite/Sprite.h"

class BackGraund : public IGameObject
{
public:

	// IGameObject
	void Init() override;
	void Draw() override;

private:

	Sprite m_sprite;
};