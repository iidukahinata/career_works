/**
* @file    UIText.cpp
* @brief
*
* @date	   2022/06/10 2022年度初版
* @author  飯塚陽太
*/


#include "UIText.h"
#include "../GameObject/GameMaster.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Scene/Scene.h"

void TextUI::Draw()
{
    if (m_isDraw)
    {
        m_sprite.Draw(m_transform.GetWorldMatrixXM());
    }
}

void TextUI::SpriteInit(std::string_view name) noexcept
{
    // 頂点レイアウト作成
    D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
        { "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    SpriteDesc spriteDesc;
    spriteDesc.vsShader = "assets/Shader/Texture2DVS.cso";
    spriteDesc.psShader = "assets/Shader/ColorTecture2DPS.cso";

    spriteDesc.layout = vertexDesc;
    spriteDesc.layoutSize = ARRAYSIZE(vertexDesc);
    spriteDesc.height = 1.f;
    spriteDesc.width = (float)Window::Get().GetWindowHeight() / (float)Window::Get().GetWindowWidth();

    spriteDesc.filePath = name;

    m_sprite.Init(spriteDesc);
}

void TextUI::SetIsDraw(bool isDraw) noexcept
{
    m_isDraw = isDraw;
}

void TextUI::ChangeColor() noexcept
{
}

void TextUIManager::Awake()
{
    if (m_scene->GetName() == "Title")
    {
        TitleUIInit();
    }
    else if (m_scene->GetName() == "Select")
    {
    }
    else if (m_scene->GetName() == "Game")
    {
        GameUIInit();
    }
    else if (m_scene->GetName() == "Edit")
    {
    }
}

void TextUIManager::Init()
{
    for (auto& text : m_texts)
    {
        text.Init();
    }
}

void TextUIManager::Draw()
{
    for (auto& text : m_texts)
    {
        text.Draw();
    }
}

void TextUIManager::TitleUIInit()
{
    TextUI text;

    text.SpriteInit("assets/Imqube/UI/PressEnterKey.png");
    text.GetTransform().SetPosition(Math::Vector3(0, -0.7f, 0));
    text.GetTransform().SetScale(Math::Vector3(0.9f, 0.5f, 1));

    m_texts.push_back(text);
}

void TextUIManager::SelectUIInit()
{
}

void TextUIManager::GameUIInit()
{
    TextUI text;

    text.SpriteInit("assets/Imqube/UI/GoNextStage.png");
    text.SetIsDraw(false);
    m_texts.push_back(text);

    text.SpriteInit("assets/Imqube/UI/GoStageSelect.png");
    text.SetIsDraw(false);
    m_texts.push_back(text);

    text.SpriteInit("assets/Imqube/UI/Restart.png");
    text.SetIsDraw(false);
    m_texts.push_back(text);
}