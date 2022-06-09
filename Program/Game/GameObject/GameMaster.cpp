/**
* @file    GameMaster.cpp
* @brief
*
* @date	   2022/06/08 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/


#include "GameMaster.h"
#include "../GameObject/Player.h"
#include "../Scene/GameScene.h"
#include "../Scene/EditScene.h"
#include "SubSystem/Scene/Scene.h"
#include "SubSystem/Scene/SceneManager.h"
#include "SubSystem/Input/Input.h"
#include "SubSystem/Resource/ResourceManager.h"

void GameMaster::Init()
{
    if (m_scene->GetName() == "Title")
    {
        m_audioClip = ResourceManager::Get().Load<AudioClip>("assets/Imqube/Wav/BGM_GAMETITLE.wav");
        m_nowScene = NowScene::Title;
    }
    else if (m_scene->GetName() == "Select")
    {
        m_audioClip = ResourceManager::Get().Load<AudioClip>("assets/Imqube/Wav/BGM_GAMEMENU.wav");
        m_nowScene = NowScene::Select;
    }
    else if (m_scene->GetName() == "Game")
    {
        m_audioClip = ResourceManager::Get().Load<AudioClip>("assets/Imqube/Wav/BGM_LEVEL1.wav");
        m_nowScene = NowScene::Game;
    }
    else if (m_scene->GetName() == "Edit")
    {
        m_nowScene = NowScene::Edit;
    }

    m_player = dynamic_cast<Player*>(m_scene->GetGameObject("player"));

    m_audioSpeaker.SetIsLoop(true);
    m_audioSpeaker.SetAudioClip(m_audioClip, true);
}

void GameMaster::Update()
{
    switch (m_nowScene)
    {
    case NowScene::Title: TitleUpdate(); break;
    case NowScene::Select: SelectUpdate(); break;
    case NowScene::Game: GameUpdate(); break;
    case NowScene::Edit: EditUpdate(); break;
    case NowScene::None: break;
    default: break;
    }
}

const char* GameMaster::GetName()
{
    return "GameMaster";
}

int& GameMaster::LoadWorldNum() noexcept
{
    static int worldNum = 1;
    return worldNum;
}

int& GameMaster::LoadStageNum() noexcept
{
    static int stageNum = 0;
    return stageNum;
}

GameMaster::NowScene GameMaster::GetNowScene() noexcept
{
    return m_nowScene;
}

void GameMaster::TitleUpdate() noexcept
{
}

void GameMaster::SelectUpdate() noexcept
{
    if (Input::Get().GetKeyStateTrigger(Button::Up))
    {
        LoadWorldNum() = (++LoadWorldNum()) % maxWorldNum;
    }
    if (Input::Get().GetKeyStateTrigger(Button::Down))
    {
        LoadWorldNum() = (LoadWorldNum() + maxWorldNum - 1) % maxWorldNum;
    }
    if (Input::Get().GetKeyStateTrigger(Button::Left))
    {
        LoadStageNum() = (++LoadWorldNum()) % maxWorldNum;
    }
    if (Input::Get().GetKeyStateTrigger(Button::Right))
    {
        LoadStageNum() = (LoadWorldNum() + maxWorldNum - 1) % maxWorldNum;
    }
    if (Input::Get().GetKeyStateTrigger(Button::Return))
    {
        if (LoadWorldNum() == 0)
        {
            m_scene->GetSceneManager()->ChangeScene<EditScene>();
        }
        else
        {
            m_scene->GetSceneManager()->ChangeScene<GameScene>();
        }
    }
}

void GameMaster::GameUpdate() noexcept
{
    if (Input::Get().GetKeyStateTrigger(Button::Return))
    {
        m_nowScene = NowScene::Game_Pauose;
    }

    if (m_player->isGameOver())
    {
        m_nowScene = NowScene::Game_GameOver;
    }
}

void GameMaster::EditUpdate() noexcept
{
}