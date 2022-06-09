/**
* @file    EditManager.h
* @brief
*
* @date	   2022/06/08 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/
#pragma once


#include "SubSystem/Scene/GameObject.h"

class EditManager : public IGameObject
{
public:

	void Init() override;
	void Update() override;

private:

	void EditGui();

private:

	class Stage* m_stage = nullptr;
};