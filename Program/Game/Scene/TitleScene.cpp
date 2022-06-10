/**
* @file    TitleScene.cpp
* @brief
*
* @date	   2022/06/03 2022îNìxèâî≈
* @author  î—íÀózëæ
*/


#include "TitleScene.h"

#include "SubSystem/Renderer/Drawings/Light/Light.h"
#include "SubSystem/Scene/SceneManager.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Input/Input.h"

#include "../GameObject/GameMaster.h"
#include "../GameObject/TitleString.h"
#include "../GameObject/TitlePlayer.h"
#include "../GameObject/BackGraund.h"
#include "../GameObject/UIText.h"

void TitleScene::Init()
{
	m_lightMap.Init();

	m_mainCamera = std::make_unique<Camera>();
	m_mainCamera->GetTransform().LockAt(Math::Vector3::Zero);

	m_directionalLight.Init(&m_lightMap);
	m_directionalLight.SetDirection(Math::Vector4(0.5f, -0.5f, -1.f, 0.f));
	m_directionalLight.SetColor(Math::Vector4(1.f));
	m_directionalLight.SetIntensity(1);
	m_lightMap.SetAmbient(Math::Vector4(0.4f));

	AddGameObject(new GameMaster);
	AddGameObject(new TitlePlayer);
	AddGameObject(new TitleString);
	AddGameObject(new TextUIManager);

	IScene::Init();
}

void TitleScene::Update()
{
	if (Input::Get().GetKeyStateTrigger(Button::Return))
	{
		if (auto player = dynamic_cast<TitlePlayer*>(GetGameObject("TitlePlayer")))
		{
			player->StartScreenOutAnim();
		}
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