/**
* @file    Message.h
* @brief
*
* @date	   2022/06/02 2022年度初版
* @author  飯塚陽太
*/


#include "Message.h"
#include "Stage.h"
#include "SubSystem/Scene/Scene.h"

void Message::Init()
{
    m_stage = dynamic_cast<Stage*>(m_scene->GetGameObject("stage"));
}

void Message::Update()
{  
    if (auto mass = m_stage->GetMassData(m_massPos))
    {
        isDraw = mass->GetType() == MassType::PLAYER;
    }
    else
    {
        isDraw = false;
    }
}

void Message::Draw()
{
    if (isDraw)
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
    spriteDesc.filePath = std::string("assets/ImqubeTex/Hint/Hint_" + std::to_string(id) + ".jpg").c_str();
    spriteDesc.layout = vertexDesc;
    spriteDesc.layoutSize = ARRAYSIZE(vertexDesc);

    // モデル行列のスケール値で大きさ調整予定なので 1 を指定。
    spriteDesc.width = spriteDesc.height = 1.f;

    m_sprite.Init(spriteDesc);
}

void Message::SetDrawMode(bool isDraw) noexcept
{
    this->isDraw = isDraw;
}