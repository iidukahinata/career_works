/**
* @file    GameScene.cpp
* @brief
*
* @date	   2022/04/13 2022”N“x‰”Å
* @version 1.00
* @author  ”Ñ’Ë—z‘¾
* @note
*/


#include "GameScene.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Input/Input.h"
#include "../GameObject/Player.h"
#include "../GameObject/Road.h"
#include "SubSystem/Renderer/Drawings/Effect/PostEffect/Bloom.h"
#include "SubSystem/Renderer/Drawings/Effect/PostEffect/Monotone.h"
#include "SubSystem/Renderer/Drawings/Effect/PostEffect/DepthOfField.h"

Math::Vector4 dir = { 0.5f, -0.5f, -1.f, 0.f };

void CameraMove(Camera* camera)
{
	Math::Vector3 rot;
	if (Input::Get().GetKeyStatePress(Button::Lshift))
	{
		rot = camera->GetTransform().GetRotation();
		if (Input::Get().GetKeyStatePress(Button::W)) {
			rot.x -= 0.02f;
		}
		if (Input::Get().GetKeyStatePress(Button::S)) {
			rot.x += 0.02f;
		}
		if (Input::Get().GetKeyStatePress(Button::A)) {
			rot.y -= 0.02f;
		}
		if (Input::Get().GetKeyStatePress(Button::D)) {
			rot.y += 0.02f;
		}

		camera->GetTransform().SetRotation(rot);
	}
	else
	{
		rot = camera->GetTransform().GetPosition();
		if (Input::Get().GetKeyStatePress(Button::W)) {
			rot.z += 0.02f;
		}
		if (Input::Get().GetKeyStatePress(Button::S)) {
			rot.z -= 0.02f;
		}
		if (Input::Get().GetKeyStatePress(Button::A)) {
			rot.x -= 0.02f;
		}
		if (Input::Get().GetKeyStatePress(Button::D)) {
			rot.x += 0.02f;
		}

		camera->GetTransform().SetPosition(rot);
	}
}

void LightMove(DirectionalLight* light)
{
	if (Input::Get().GetKeyStatePress(Button::Up)) {
		dir.y += 0.1f;
	}
	if (Input::Get().GetKeyStatePress(Button::Down)) {
		dir.y -= 0.1f;
	}
	if (Input::Get().GetKeyStatePress(Button::L)) {
		dir.x -= 0.1f;
	}
	if (Input::Get().GetKeyStatePress(Button::J)) {
		dir.x += 0.1f;
	}
	if (Input::Get().GetKeyStatePress(Button::I)) {
		dir.z += 0.1f;
	}
	if (Input::Get().GetKeyStatePress(Button::K)) {
		dir.z -= 0.1f;
	}
	light->SetDirection(dir);
}

void GameScene::Awake()
{
	AddGameObject(new Road);
}

void GameScene::Init()
{
	m_lightMap.Init();
	postprocessing.Init();
	skyBox.Init("assets/SkyBox/skybox.dds");

	m_mainCamera = std::make_unique<Camera>();
	m_mainCamera->GetTransform().LockAt(Math::Vector3::Zero);

	m_directionalLight.Init(&m_lightMap);
	m_directionalLight.SetDirection(dir);
	m_directionalLight.SetColor({ 1.f });
	m_directionalLight.SetIntensity(1);
	m_lightMap.SetAmbient({ 0.4f });
}

void GameScene::Update()
{
	IScene::Update();

	CameraMove(m_mainCamera.get());
	LightMove(&m_directionalLight);

	m_mainCamera->Update(Math::Vector3::Zero, Math::Vector3::Zero);

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