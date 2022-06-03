/**
* @file    GameScene.cpp
* @brief
*
* @date	   2022/06/03 2022îNìxèâî≈
* @author  î—íÀózëæ
*/


#include "GameScene.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Input/Input.h"
#include "../GameObject/Stage.h"
#include "../GameObject/Player.h"
#include "../GameObject/CameraMove.h"

void GameScene::Awake()
{
	AddGameObject(new Stage);
}

void GameScene::Init()
{
	m_lightMap.Init();

	m_mainCamera = std::make_unique<Camera>();
	m_mainCamera->GetTransform().LockAt(Math::Vector3::Zero);

	m_directionalLight.Init(&m_lightMap);
	m_directionalLight.SetDirection(Math::Vector4(0.5f, -0.5f, -1.f, 0.f));
	m_directionalLight.SetColor({ 1.f });
	m_directionalLight.SetIntensity(1);
	m_lightMap.SetAmbient({ 0.4f });

	AddGameObject(new CameraMove);

	IScene::Init();
}

void GameScene::Update()
{
	IScene::Update();

	m_lightMap.Update(m_mainCamera->GetTransform().GetWoldPosition());
}

void GameScene::Draw()
{
	TransformCBuffer::Get().SetProjection(m_mainCamera->GetProjectionMatrixXM());
	TransformCBuffer::Get().SetView(m_mainCamera->GetViewMatrixXM());

	IScene::Draw();
}