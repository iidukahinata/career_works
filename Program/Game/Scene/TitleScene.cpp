#include "TitleScene.h"
#include "SubSystem/Scene/SceneManager.h"
#include "SubSystem/Input/Input.h"
#include "GameScene.h"

void TitleScene::Init()
{
	IScene::Init();
}

void TitleScene::Update()
{
	if (Input::Get().GetKeyStateTrigger(Button::Return))
	{
		m_sceneManager->ChangeScene<GameScene>();
	}

	IScene::Update();
}

void TitleScene::Draw()
{
	IScene::Draw();
}