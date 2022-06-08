/**
* @file    BackGraund.cpp
* @brief
*
* @date	   2022/06/08 2022�N�x����
* @author  �ђ˗z��
*/


#include "BackGraund.h"
#include "../GameObject/GameMaster.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Timer/Timer.h"
#include "SubSystem/Scene/Scene.h"

void PartternBackGraound::Awake() noexcept
{
    // ���_���C�A�E�g�쐬
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
        m_patternCentorPositions[i].x = (i - (maxCentorPosSize / 2)) * -0.75f + 2.25f;
        m_patternCentorPositions[i].y = (i - (maxCentorPosSize / 2)) * -1.f;

        // Z�o�b�t�@�ł̏d�Ȃ�o�O��������邽��
        m_patternCentorPositions[i].z = i * -0.0001f;
    }

    m_bottomPos = m_patternCentorPositions[maxCentorPosSize - 1];
}

void PartternBackGraound::Update() noexcept
{
    for (int i = 0; i < maxCentorPosSize; ++i)
    {
        m_patternCentorPositions[i] += m_velocity;
        if (m_patternCentorPositions[i].y >= 5.f)
        {
            m_patternCentorPositions[i] = m_bottomPos;
        }
    }
}

void PartternBackGraound::Draw(UINT index) noexcept
{
    if (index >= patternSize) return;

    for (int i = 0; i < maxCentorPosSize; ++i)
    {
        // ���S�_���牡���Ƀp�^�[���摜����ׂ邽�߂̏���
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
    // ���_���C�A�E�g�쐬
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
    m_transform.SetScale(Math::Vector3(2.7f, 4.5f, 0.f));

    m_parttern.Init(m_scene->GetMainCamera());

    m_master = dynamic_cast<GameMaster*>(m_scene->GetGameObject("GameMaster"));
}

void SelectBackGraund::Update()
{
    m_parttern.Update();

    switch (m_animMode)
    {
    case AnimMode::ScreenIn: ScreenInAnimUpdate(); break;
    case AnimMode::ScreenOut: ScreenOutAnimUpdate(); break;
    case AnimMode::None: break;
    default: break;
    }
}

void SelectBackGraund::Draw()
{
    if (m_transform.GetPosition().y < 1.f)
    {
        m_parttern.Draw(m_master->LoadWorldNum());
    }

    m_backSprite.Draw(m_transform.GetWorldMatrixXM());
}

void SelectBackGraund::ScreenInAnimUpdate() noexcept
{
    auto pos = m_transform.GetPosition();
    pos.y += m_speed;
    m_transform.SetPosition(pos);

    if (pos.y < -1.2f)
    {
        m_animMode = AnimMode::None;

        pos.y = -1.2f;
        m_transform.SetPosition(pos);
    }
}

void SelectBackGraund::ScreenOutAnimUpdate() noexcept
{
    auto pos = m_transform.GetPosition();
    pos.y -= m_speed;
    m_transform.SetPosition(pos);

    if (pos.y >= 6.f)
    {
        m_animMode = AnimMode::None;

        pos.y = 6.f;
        m_transform.SetPosition(pos);
    }
}