/**
* @file    TitleScene.cpp
* @brief
*
* @date	   2022/06/03 2022年度初版
* @author  飯塚陽太
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
#include "../GameObject/Effect.h"

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

	// 透過処理の部分でバグがあるため使用しない。
	// 多段階レンダリングを作成すれば対応できる。
	//AddGameObject(new Effect); 

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