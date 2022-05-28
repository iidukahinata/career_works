/**
* @file    TitleScene.h
* @brief
*
* @date	   2022/05/28 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/
#pragma once


#include"SubSystem/Scene/Scene.h"
#include "SubSystem/Renderer/Drawings/Light/Light.h"
#include "SubSystem/Renderer/Drawings/Effect/Postprocessing.h"
#include "SubSystem/Renderer/Drawings/SkyBox/SkyBox.h"


class TitleScene : public IScene
{
public:

	void Init() override;
	void Update() override;
	void Draw() override;
};