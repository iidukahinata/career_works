/**
* @file    BackGraund.cpp
* @brief
*
* @date	   2022/06/03 2022年度初版
* @author  飯塚陽太
*/


#include "BackGraund.h"
#include "SubSystem/Window/Window.h"

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

    m_transform.SetPosition(Math::Vector3());
    m_transform.SetScale(Math::Vector3(2, 2, 1));
}

void BackGraund::Draw()
{
    m_sprite.Draw(m_transform.GetWorldMatrixXM());
}