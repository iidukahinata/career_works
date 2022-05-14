

#include "Player.h"
#include "SubSystem/Scene/Scene.h"
#include "SubSystem/Input/Input.h"

/**
* @brief	初期化
*/
void Player::Init()
{
	// 頂点レイアウト作成
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT"  , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BINORMAL" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	ModelDesc modelDesc;
	modelDesc.modelFilePath = "assets/Renault/Renault.fbx";
	modelDesc.layout = vertexDesc;
	modelDesc.layoutSize = ARRAYSIZE(vertexDesc);
	modelDesc.vsShader = "assets/Shader/PBR_VS.cso";
	modelDesc.psShader = "assets/Shader/PBR_PS.cso";
	m_model.Init(modelDesc);

	m_transform.SetScale(Math::Vector3(0.01f));
}

/**
* @brief	更新
*/
void Player::Update()
{
	auto rot = m_transform.GetRotation();
	if (Input::Get().GetKeyStatePress(Button::F1)) 
	{
		rot.z += 0.1;
	}
	else if (Input::Get().GetKeyStatePress(Button::Up))
	{
		rot.x += 0.1;
	}
	else if (Input::Get().GetKeyStatePress(Button::Left))
	{
		rot.y += 0.1;
	}
	m_transform.SetRotation(rot);
}

/**
* @brief	描画
*/
void Player::Draw()
{
	m_model.Draw(m_transform.GetWorldMatrixXM());
}