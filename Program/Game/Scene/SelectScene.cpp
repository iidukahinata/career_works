/**
* @file    SelectScene.cpp
* @brief
*
* @date	   2022/06/08 2022îNìxèâî≈
* @author  î—íÀózëæ
*/


#include "SelectScene.h"

#include "SubSystem/Renderer/Drawings/Light/Light.h"
#include "SubSystem/Scene/SceneManager.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Input/Input.h"

#include "../GameObject/BackGraund.h"
#include "../GameObject/GameMaster.h"

void SelectScene::Init()
{
	m_lightMap.Init();

	m_mainCamera = std::make_unique<Camera>();
	m_mainCamera->GetTransform().SetPosition(Math::Vector3(0.f, 0.f, -15.f));
	m_mainCamera->GetTransform().LockAt(Math::Vector3::Zero);

	m_directionalLight.Init(&m_lightMap);
	m_directionalLight.SetDirection(Math::Vector4(0.5f, -0.5f, -1.f, 0.f));
	m_directionalLight.SetColor(Math::Vector4(1.f));
	m_directionalLight.SetIntensity(1);
	m_lightMap.SetAmbient(Math::Vector4(0.4f));

	AddGameObject(new GameMaster);
	AddGameObject(new SelectBackGraund);

	IScene::Init();

	m_master = dynamic_cast<GameMaster*>(GetGameObject("GameMaster"));
}

void SelectScene::Update()
{
	IScene::Update();

	m_lightMap.Update(m_mainCamera->GetTransform().GetWoldPosition());
}

void SelectScene::Draw()
{
	TransformCBuffer::Get().SetProjection(m_mainCamera->GetProjectionMatrixXM());
	TransformCBuffer::Get().SetView(m_mainCamera->GetViewMatrixXM());

	IScene::Draw();
}