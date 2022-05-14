

#include "Road.h"
#include "SubSystem/Scene/Scene.h"

/**
* @brief	������
*/
void Road::Init()
{
	m_transform.SetPosition(Math::Vector3(0.f, -0.5f, 0.f));
	m_transform.SetRotation(Math::Vector3(DirectX::XMConvertToRadians(-90.f), 0.f, 0.f));
	m_transform.SetScale(Math::Vector3(10.f));

	//���_���C�A�E�g�쐬
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0							, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	QuadDesc quadDesc;
	quadDesc.filePath = "assets/Dice/texture/RED_SCISSOR.png";
	quadDesc.layout = vertexDesc;
	quadDesc.layoutSize = ARRAYSIZE(vertexDesc);
	quadDesc.psShader = "assets/Shader/LambertPS.cso";
	quadDesc.vsShader = "assets/Shader/LambertVS.cso";
	m_quad.Init(quadDesc);
}

/**
* @brief	�X�V
*/
void Road::Update()
{}

/**
* @brief	�`��
*/
void Road::Draw()
{
	m_quad.Draw(m_transform.GetWorldMatrixXM());
}