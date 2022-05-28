/**
* @file    GameScene.cpp
* @brief
*
* @date	   2022/05/28 2022îNìxèâî≈
* @version 1.00
* @author  î—íÀózëæ
* @note
*/


#include "GameScene.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Input/Input.h"
#include "../GameObject/Player.h"
#include "../GameObject/Stage.h"
#include "../GameObject/CameraMove.h"
#include "SubSystem/Renderer/Drawings/Effect/PostEffect/Bloom.h"
#include "SubSystem/Renderer/Drawings/Effect/PostEffect/Monotone.h"
#include "SubSystem/Renderer/Drawings/Effect/PostEffect/DepthOfField.h"

void GameScene::Awake()
{
	AddGameObject(new Player);
	AddGameObject(new Stage);
}

void GameScene::Init()
{
	m_lightMap.Init();
	postprocessing.Init();
	skyBox.Init("assets/SkyBox/skybox.dds");

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

	postprocessing.Update();

	m_lightMap.Update(m_mainCamera->GetTransform().GetWoldPosition());
}

void GameScene::Draw()
{
	TransformCBuffer::Get().SetProjection(m_mainCamera->GetProjectionMatrixXM());
	TransformCBuffer::Get().SetView(m_mainCamera->GetViewMatrixXM());

	skyBox.Draw(m_mainCamera->GetTransform().GetWoldPosition());

	IScene::Draw();

	Transform camera2D;
	camera2D.SetPosition(Math::Vector3(0.f, 0.f, -1.f));
	TransformCBuffer::Get().SetView(DirectX::XMMatrixInverse(nullptr, camera2D.GetWorldMatrixXM()));
	TransformCBuffer::Get().SetProjection(m_mainCamera->GetOrthographicMatrixXM());
	
	postprocessing.Draw();
}