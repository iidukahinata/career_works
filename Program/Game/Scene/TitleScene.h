/**
* @file    TitleScene.h
* @brief
*
* @date	   2022/06/03 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include"SubSystem/Scene/Scene.h"

class TitleScene : public IScene
{
public:

	void Init() override;
	void Update() override;
	void Draw() override;
};