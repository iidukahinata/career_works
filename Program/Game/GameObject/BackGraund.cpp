/**
* @file    BackGraund.cpp
* @brief
*
* @date	   2022/06/03 2022年度初版
* @author  飯塚陽太
*/


#include "BackGraund.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Timer/Timer.h"

void BackGraund::Init()
{
    // 頂点レイアウト作成
    D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
        { "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    SpriteDesc spriteDesc;
    spriteDesc.vsShader = "assets/Shader/Texture2DVS.cso";
    spriteDesc.psShader = "assets/Shader/Texture2DPS.cso";
    spriteDesc.filePath = "assets/Imqube/Back/Title.png";

    spriteDesc.layout = vertexDesc;
    spriteDesc.layoutSize = ARRAYSIZE(vertexDesc);
    spriteDesc.height = 1.f;
    spriteDesc.width = (float)Window::Get().GetWindowHeight() / (float)Window::Get().GetWindowWidth();

    m_sprite.Init(spriteDesc);

    m_transform.SetScale(Math::Vector3(3.f, 0.f, 1.f));
}

void BackGraund::Update()
{
    switch (m_animMode)
    {
    case BackGraund::Opne: OpneAnimUpdate(); break;
    case BackGraund::Up: UpAnimUpdate(); break;
    case BackGraund::Down: DownAnimUpdate(); break;
    default: break;
    }
}

void BackGraund::Draw()
{
    m_sprite.Draw(m_transform.GetWorldMatrixXM());
}

void BackGraund::OpneAnimUpdate() noexcept
{
    m_addSpeed < 0.1f ? m_addSpeed += 0.001f : m_addSpeed += 0.05f;
    if (m_addSpeed > 1.f) m_addSpeed = 1.f;

    m_speed += (m_addSpeed * Timer::Get().GetDeltaTime());
    m_transform.SetScale(m_transform.GetScale() + Math::Vector3(-m_speed, m_speed * 0.5f, 0.f));

    constexpr float changeAnimSizeX = 1.5f;
    if (m_transform.GetScale().x <= changeAnimSizeX)
    {
        m_animMode = AnimMode::Up;
        m_transform.SetScale(Math::Vector3(1.5f, 0.75f, 1.f));
    }
}

void BackGraund::UpAnimUpdate() noexcept
{
    m_animMode = AnimMode::Down;
}

void BackGraund::DownAnimUpdate() noexcept
{
    m_animMode = AnimMode::None;
}