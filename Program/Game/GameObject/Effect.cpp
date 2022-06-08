/**
* @file    Effect.cpp
* @brief
*
* @date	   2022/06/08 2022年度初版
* @author  飯塚陽太
*/


#include "Effect.h"
#include <random>
#include "SubSystem/Window/Window.h"
#include "SubSystem/Renderer/D3D11/D3D11GrahicsDevice.h"

std::mt19937 mt19937;

void Effect::Init()
{
    // seed 値を決定。
    std::random_device random;
    mt19937.seed(random());

    // 頂点レイアウト作成
    D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
        { "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    SpriteDesc spriteDesc;
    spriteDesc.vsShader = "assets/Shader/Texture2DVS.cso";
    spriteDesc.psShader = "assets/Shader/ColorTecture2DPS.cso";
    spriteDesc.filePath = "assets/Imqube/Back/effect.png";

    spriteDesc.layout = vertexDesc;
    spriteDesc.layoutSize = ARRAYSIZE(vertexDesc);
    spriteDesc.height = 1.f;
    spriteDesc.width = (float)Window::Get().GetWindowHeight() / (float)Window::Get().GetWindowWidth();

    m_sprite.Init(spriteDesc);

    m_constantBuffer.Create(sizeof(ConstantBufferColor));

    SetColor(Math::Vector4(1.f));
}

void Effect::Update()
{
    auto numCreate = mt19937() % 30;
    if (numCreate < 1)
    {
        m_effects.push_back(CreateEffectData());
    }

    for (int i = 0; i < m_effects.size(); ++i)
    {
        EffectDataUpdate(&m_effects[i], i);
    }
}

void Effect::Draw()
{
    auto& renderStates = D3D11GrahicsDevice::Get().GetRenderStates();
    renderStates.SetBlendState(renderStates.m_additiveTransparencyBlend.Get());

    m_constantBuffer.PSSet(3);

    for (int i = 0; i < m_effects.size(); ++i)
    {
        SetColor(m_effects[i].m_color);
        m_sprite.Draw(m_effects[i].m_transform.GetWorldMatrixXM());
    }

    renderStates.SetBlendState(renderStates.m_alphaEnabledBlend.Get());
}

void Effect::SetColor(const Math::Vector4& color) noexcept
{
    ConstantBufferColor buffer = { color };
    m_constantBuffer.Update(buffer);
}

void Effect::EffectDataUpdate(EffectData* data, int index) noexcept
{
    ++(data->m_timeCount);

    auto scale = data->m_transform.GetScale();
    if ((data->m_maxTmeCount / 2) > data->m_timeCount)
    {
        scale += Math::Vector3(0.02f, 0.02f, 0.f);
    }
    else 
    {
        scale -= Math::Vector3(0.02f, 0.02f, 0.f);
    }
    data->m_transform.SetScale(scale);

    constexpr float speed = 0.005f;
    auto pos = data->m_transform.GetPosition();
    pos += data->m_direction * speed;
    data->m_transform.SetPosition(pos);

    if (data->m_maxTmeCount <= data->m_timeCount)
    {
        m_effects.erase(m_effects.begin() + index);
    }
}

Effect::EffectData Effect::CreateEffectData() const noexcept
{
    EffectData effectData;

    // timeCount の範囲を 40～80 の間に納める。
    effectData.m_maxTmeCount += (mt19937() % 40) - 20;

    if ((mt19937() % 100) <= 98)
    {
        effectData.m_color = Math::Vector4(1.f, 242.f / 255.f, 0.f, 0.3f);
    }

    // 16 方向しか扱わない。
    auto rad = Math::ToRadian(static_cast<float>(mt19937() % 16) * 22.5f);
    effectData.m_direction.x = sin(rad);
    effectData.m_direction.y = cos(rad);
    effectData.m_direction.Normalize();

    effectData.m_direction.x *= (float)Window::Get().GetWindowHeight() / (float)Window::Get().GetWindowWidth();

    effectData.m_transform.SetScale(Math::Vector3());

    return effectData;
}