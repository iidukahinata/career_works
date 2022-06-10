/**
* @file    TitleString.cpp
* @brief
*
* @date	   2022/06/10 2022�N�x����
* @author  �ђ˗z��
*/


#include "TitleString.h"
#include "SubSystem/Window/Window.h"
#include "SubSystem/Timer/Timer.h"

void TitleString::Awake()
{
    // ���_���C�A�E�g�쐬
    D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
        { "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    SpriteDesc spriteDesc;
    spriteDesc.vsShader = "assets/Shader/Texture2DVS.cso";
    spriteDesc.psShader = "assets/Shader/ColorTecture2DPS.cso";
    spriteDesc.filePath = "assets/Imqube/Back/TitleString.png";

    spriteDesc.layout = vertexDesc;
    spriteDesc.layoutSize = ARRAYSIZE(vertexDesc);
    spriteDesc.height = 1.f;
    spriteDesc.width = (float)Window::Get().GetWindowHeight() / (float)Window::Get().GetWindowWidth();

    m_sprite.Init(spriteDesc);
}

void TitleString::Init()
{
    m_constantBuffer.Create(sizeof(ConstantBufferColor));

    SetColor(Math::Vector4(1.f));
    m_transform.SetScale(Math::Vector3(3.f, 0.f, 1.f));

    m_animator.RegisterAnimation("Opne", [this] { OpneAnim(); });
    m_animator.RegisterAnimation("UpDown", [this] { UpDownAnim(); });
    m_animator.RegisterAnimation("FadeOut", [this] { FadeOutAnim(); });

    m_animator.SetAnimation("Opne");
}

void TitleString::Update()
{
    m_animator.Update();
}

void TitleString::Draw()
{
    m_constantBuffer.PSSet(3);

    m_sprite.Draw(m_transform.GetWorldMatrixXM());
}

const char* TitleString::GetName()
{
    return "TitleString";
}

void TitleString::StartUpDownAnim() noexcept
{
    m_animator.SetAnimation("UpDown");

    m_addSpeed = 0.f;
    m_speed = 0.01f;
}

void TitleString::StartFadeOutAnim() noexcept
{
    m_animator.SetAnimation("FadeOut");

    m_addSpeed = 0.03f;
    m_speed = 1.f;
}

bool TitleString::IsNoneAnim() const noexcept
{
    return !m_animator.IsPlaying();
}

void TitleString::SetColor(const Math::Vector4& color) noexcept
{
    ConstantBufferColor buffer = { color };
    m_constantBuffer.Update(buffer);
}

void TitleString::OpneAnim() noexcept
{
    // �������o�Ă��āA�������}�ɏo�Ă���悤�ɂ��Ă���B
    m_addSpeed < 0.03f ? m_addSpeed += 0.001f : m_addSpeed += 0.025f;
    if (m_addSpeed > 1.f) m_addSpeed = 1.2f;

    m_speed += (m_addSpeed * Timer::Get().GetDeltaTime());
    m_transform.SetScale(m_transform.GetScale() + Math::Vector3(-m_speed, m_speed * 0.5f, 0.f));

    constexpr float changeAnimSizeX = 1.5f;
    if (m_transform.GetScale().x <= changeAnimSizeX)
    {
        m_transform.SetScale(Math::Vector3(1.5f, 0.75f, 1.f));

        m_animator.StopAnimation();
    }
}

void TitleString::UpDownAnim() noexcept
{
    m_speed -= 0.000075f;

    auto pos = m_transform.GetPosition();
    pos.y += m_speed;
    m_transform.SetPosition(pos);

    // �ő�l 12 �ɒ������Ă���B
    m_addSpeed += 7.f + m_speed * 500.f;

    // �㉺�ɐL�т�悤�ȓ����������Ă���B
    // ���\�G�ȏ����ł��B�{���͂����Ƃ�������������Ǝv���B
    auto sin = std::sin(Math::ToRadian(m_addSpeed));
    Math::Vector3 addScale = Math::Vector3(sin * 0.3f, -sin * 0.3f, 0.f);

    // �����Ő������Ȃ��Ȃ��Ă����悤�ȕ\���������Ă���B
    if (m_speed < 0.f)
    {
        constexpr float maxDistance = 0.16f;
        addScale *= ((pos.y - 0.5f) / maxDistance);
    }
    else
    {
        constexpr float maxDistance = 0.66f;
        addScale *= ((0.66f - pos.y) / maxDistance) + 1.f;
    }

    m_transform.SetScale(addScale + Math::Vector3(1.5f, 0.75f, 1.f));

    if (pos.y < 0.5f && m_speed < 0.f)
    {
        StopTitleAnim();
    }
}

void TitleString::FadeOutAnim() noexcept
{
    m_speed -= m_addSpeed;
    if (m_speed < 0.f)m_speed = 0.f;

    SetColor(Math::Vector4(1, 1, 1, m_speed));
}

void TitleString::StopTitleAnim() noexcept
{
    m_animator.StopAnimation();

    auto pos = m_transform.GetPosition();
    pos.y = 0.5f;
    m_transform.SetPosition(pos);

    m_transform.SetScale(Math::Vector3(1.5f, 0.75f, 1.f));

    m_addSpeed = 0.f;
    m_speed = 0.f;
}