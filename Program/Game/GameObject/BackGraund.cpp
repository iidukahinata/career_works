/**
* @file    BackGraund.cpp
* @brief
*
* @date	   2022/06/08 2022年度初版
* @author  飯塚陽太
*/


#include "BackGraund.h"
#include "../GameObject/GameMaster.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Timer/Timer.h"
#include "SubSystem/Scene/Scene.h"

void PartternBackGraound::Awake() noexcept
{
    // 頂点レイアウト作成
    D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
        { "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    SpriteDesc spriteDesc;
    spriteDesc.vsShader = "assets/Shader/TextureVS.cso";
    spriteDesc.psShader = "assets/Shader/TexturePS.cso";

    spriteDesc.layout = vertexDesc;
    spriteDesc.layoutSize = ARRAYSIZE(vertexDesc);
    spriteDesc.height = 1.f;
    spriteDesc.width = (float)Window::Get().GetWindowHeight() / (float)Window::Get().GetWindowWidth();

    for (int i = 0; i < patternSize; ++i)
    {
        spriteDesc.filePath = "assets/Imqube/Back/BackMenuPattern_" + std::to_string(i) + ".bmp";
        m_sprites[i].Init(spriteDesc);
    }
}

void PartternBackGraound::Init(Camera* camera) noexcept
{
    for (int i = 0; i < maxCentorPosSize; ++i)
    {
        m_patternCentorPositions[i].x = (i - (maxCentorPosSize / 2)) * 0.75f + 1.5f;
        m_patternCentorPositions[i].y = (i - (maxCentorPosSize / 2)) * -1.f;

        m_bottomPos = m_patternCentorPositions[i];
    }
}

void PartternBackGraound::Update() noexcept
{
    for (int i = 0; i < maxCentorPosSize; ++i)
    {
        if (m_patternCentorPositions[i].y >= (5.f - 0.001f))
        {
            m_patternCentorPositions[i] = m_bottomPos;
        }

        m_patternCentorPositions[i] += m_velocity;
    }
}

void PartternBackGraound::Draw(UINT index) noexcept
{
    if (index >= patternSize) return;

    for (int i = 0; i < maxCentorPosSize; ++i)
    {
        // 中心点から横一列にパターン画像を並べるための処理
        for (int num = -15; num < 15; ++num)
        {
            auto pos = m_patternCentorPositions[i];
            pos += Math::Vector3(-0.75f * (float)num, 0.f, 0.f);
            m_transform.SetPosition(pos);
            m_sprites[index].Draw(m_transform.GetWorldMatrixXM());
        }
    }
}

void SelectBackGraund::Awake()
{
    // 頂点レイアウト作成
    D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
        { "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    SpriteDesc spriteDesc;
    spriteDesc.vsShader = "assets/Shader/Texture2DVS.cso";
    spriteDesc.psShader = "assets/Shader/Texture2DPS.cso";
    spriteDesc.filePath = "assets/Imqube/Back/BackMenu.png";

    spriteDesc.layout = vertexDesc;
    spriteDesc.layoutSize = ARRAYSIZE(vertexDesc);
    spriteDesc.height = 1.f;
    spriteDesc.width = (float)Window::Get().GetWindowHeight() / (float)Window::Get().GetWindowWidth();

    m_backSprite.Init(spriteDesc);

    m_parttern.Awake();
}

void SelectBackGraund::Init()
{
    m_transform.SetPosition(Math::Vector3(0.f, 6.f, 0.f));
    m_transform.SetScale(Math::Vector3(2.67f, 4.5f, 0.f));

    m_parttern.Init(m_scene->GetMainCamera());

    m_master = dynamic_cast<GameMaster*>(m_scene->GetGameObject("GameMaster"));

    m_animator.RegisterAnimation("ScreenIn", [this] { ScreenInAnim(); });
    m_animator.RegisterAnimation("ScreenOut", [this] { ScreenOutAnim(); });

    m_animator.SetAnimation("ScreenIn");
}

void SelectBackGraund::Update()
{
    m_parttern.Update();

    m_animator.Update();
}

void SelectBackGraund::Draw()
{
    if (m_transform.GetPosition().y < 1.f)
    {
        m_parttern.Draw(m_master->LoadWorldNum());
    }

    m_backSprite.Draw(m_transform.GetWorldMatrixXM());
}

void SelectBackGraund::ScreenInAnim() noexcept
{
    auto pos = m_transform.GetPosition();
    pos.y += m_speed;
    m_transform.SetPosition(pos);

    if (pos.y < -1.2f)
    {
        m_animator.StopAnimation();

        pos.y = -1.2f;
        m_transform.SetPosition(pos);
    }
}

void SelectBackGraund::ScreenOutAnim() noexcept
{
    auto pos = m_transform.GetPosition();
    pos.y -= m_speed;
    m_transform.SetPosition(pos);

    if (pos.y >= 6.f)
    {
        m_animator.StopAnimation();

        pos.y = 6.f;
        m_transform.SetPosition(pos);
    }
}