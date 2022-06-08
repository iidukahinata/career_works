/**
* @file    SelectScene.h
* @brief
*
* @date	   2022/06/08 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/
#pragma once


#include"SubSystem/Scene/Scene.h"

class SelectScene : public IScene
{
public:

	void Init() override;
	void Update() override;
	void Draw() override;

	const char* GetName()
	{
		return "Select";
	}

private:

	class GameMaster* m_master = nullptr;
};