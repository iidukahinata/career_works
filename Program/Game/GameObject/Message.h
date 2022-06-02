/**
* @file    Message.h
* @brief
*
* @date	   2022/06/02 2022年度初版
* @author  飯塚陽太
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

	// * stage から map 情報を取得するため。
	class Stage* m_stage = nullptr;

	Sprite m_sprite;
};