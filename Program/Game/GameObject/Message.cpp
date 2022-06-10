/**
* @file    Message.h
* @brief
*
* @date	   2022/06/09 2022年度初版
* @author  飯塚陽太
*/


#include "Message.h"
#include "Stage.h"
#include "SubSystem/Scene/Scene.h"
#include "SubSystem/Window/Window.h"

void Message::Awake()
{
    // 頂点レイアウト作成
    D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
        { "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    SpriteDesc spriteDesc;
    spriteDesc.vsShader = "assets/Shader/Texture2DVS.cso";
    spriteDesc.psShader = "assets/Shader/Texture2DPS.cso";
    spriteDesc.filePath = "assets/Imqube/Hint/Hint_Window.jpg";

    spriteDesc.layout = vertexDesc;
    spriteDesc.layoutSize = ARRAYSIZE(vertexDesc);
    spriteDesc.height = 1.f;
    spriteDesc.width = (float)Window::Get().GetWindowHeight() / (float)Window::Get().GetWindowWidth();

    m_windowSprite.Init(spriteDesc);
}

void Message::Init()
{
    m_stage = m_scene->GetGameObject<Stage>("stage");

    m_transform.SetPosition(Math::Vector3(0.f, -0.6f, 0.f));
    m_transform.SetScale(Math::Vector3(0.f * aspect.x, 0.f * aspect.y, 1.f));

    m_animator.RegisterAnimation("Open", [this] { OpenAnim(); });
    m_animator.RegisterAnimation("Close", [this] { CloseAnim(); });
}

void Message::Update()
{  
    m_animator.Update();

    if (auto mass = m_stage->GetMassData(m_massPos))
    {
        SetDrawMode(mass->GetType() == MassType::PLAYER);
    }
    else
    {
        m_stage->SetMass(m_massPos, this);
    }
}

void Message::Draw()
{
    if (m_isDraw)
    {
        m_sprite.Draw(m_transform.GetWorldMatrixXM());
    }
}

IMass::MassType Message::GetType()
{
    return MassType::MESSEGE;
}

void Message::MessegeSpriteInit(int id) noexcept
{
    // 頂点レイアウト作成
    D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
        { "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    SpriteDesc spriteDesc;
    spriteDesc.vsShader = "assets/Shader/Texture2DVS.cso";
    spriteDesc.psShader = "assets/Shader/Texture2DPS.cso";
    spriteDesc.filePath = "assets/Imqube/Hint/Hint_" + std::to_string(id) + ".png";

    spriteDesc.layout = vertexDesc;
    spriteDesc.layoutSize = ARRAYSIZE(vertexDesc);
    spriteDesc.height = 1.f;
    spriteDesc.width = (float)Window::Get().GetWindowHeight() / (float)Window::Get().GetWindowWidth();

    m_sprite.Init(spriteDesc);
}

void Message::SetDrawMode(bool isDraw) noexcept
{
    if (m_isDraw == false && isDraw)
    {
        m_animator.SetAnimation("Open");
        m_isDraw = true;
    }
    if (m_isDraw && isDraw == false)
    {
        m_animator.SetAnimation("Close");
    }
}

void Message::OpenAnim() noexcept
{
    constexpr float m_maxSize = 0.3f;

    m_nowSize += 0.05f;
    m_transform.SetScale(Math::Vector3(m_nowSize * aspect.x, m_nowSize * aspect.y, 1.f));

    if (m_nowSize >= m_maxSize)
    {
        m_transform.SetScale(Math::Vector3(m_maxSize * aspect.x, m_maxSize * aspect.y, 1.f));
        m_animator.StopAnimation();
    }
}

void Message::CloseAnim() noexcept
{
    constexpr float m_minSize = 0.f;

    m_nowSize += -0.05f;
    m_transform.SetScale(Math::Vector3(m_nowSize * aspect.x, m_nowSize * aspect.y, 1.f));

    if (m_nowSize <= m_minSize)
    {
        m_transform.SetScale(Math::Vector3(m_minSize * aspect.x, m_minSize * aspect.y, 1.f));
        m_animator.StopAnimation();
        m_isDraw = false;
    }
}