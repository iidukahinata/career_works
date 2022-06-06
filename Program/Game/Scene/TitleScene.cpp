/**
* @file    TitleScene.cpp
* @brief
*
* @date	   2022/06/03 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/


#include "TitleScene.h"
#include "SubSystem/Renderer/Drawings/Light/Light.h"
#include "SubSystem/Scene/SceneManager.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Input/Input.h"
#include "GameScene.h"
#include "../GameObject/BackGraund.h"

void TitleScene::Init()
{
	m_lightMap.Init();

	m_mainCamera = std::make_unique<Camera>();
	m_mainCamera->GetTransform().LockAt(Math::Vector3::Zero);

	m_directionalLight.Init(&m_lightMap);
	m_directionalLight.SetDirection(Math::Vector4(0.5f, -0.5f, -1.f, 0.f));
	m_directionalLight.SetColor({ 1.f });
	m_directionalLight.SetIntensity(1);
	m_lightMap.SetAmbient({ 0.4f });

	AddGameObject(new BackGraund);

	IScene::Init();
}

void TitleScene::Update()
{
	if (Input::Get().GetKeyStateTrigger(Button::Return))
	{
		m_sceneManager->ChangeScene<GameScene>();
	}

	IScene::Update();

	m_lightMap.Update(m_mainCamera->GetTransform().GetWoldPosition());
}

void TitleScene::Draw()
{
	TransformCBuffer::Get().SetProjection(m_mainCamera->GetProjectionMatrixXM());
	TransformCBuffer::Get().SetView(m_mainCamera->GetViewMatrixXM());

	IScene::Draw();
}