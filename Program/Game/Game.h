/**
* @file    Game.h
* @brief
*
* @date	   2022/04/29 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include "SubSystem/Scene/SceneManager.h"

class Game
{

public:

	void Init();	

	void Update(double deltatime);

	void Render(double deltatime);

	void Exit();

private:

	SceneManager m_sceneManager;
};