/**
* @file    EditManager.cpp
* @brief
*
* @date	   2022/06/08 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/


#include "EditManager.h"
#include "SubSystem/Scene/Scene.h"
#include "Stage.h"

#include "ThirdParty/imgui/imgui.h"
#include "SubSystem/Gui/MyGui.h"

void EditManager::Init()
{
	m_stage = dynamic_cast<Stage*>(m_scene->GetGameObject("stage"));

	//MyGui::Get().AddWidget([this] { EditGui(); });
}

void EditManager::Update()
{
}

void EditManager::EditGui()
{
}