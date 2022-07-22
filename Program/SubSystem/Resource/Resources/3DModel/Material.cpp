/**
* @file    Material.cpp
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/


#include "Material.h"
#include "Texture.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "ThirdParty/directxtex/include/d3dx12.h"

Material::Material()
{
	// ���ݒ�
	SetVSShader("assets/Resource/Shader/PBR_VS.cso");
	SetPSShader("assets/Resource/Shader/PBR_PS.cso");
}

void Material::SaveToFile(StringView filePath)
{
	const auto path = ConvertProprietaryFormat(filePath);

	FileStream fileStream;
	if (!fileStream.CreateFileAndLoad(path, OpenMode::Write_Mode))
		return;

	fileStream.Write(m_textures.size());
	for (auto& texture : m_textures)
	{
		fileStream.Write(texture->GetName());
	};
}

bool Material::LoadFromFile(StringView filePath)
{
	const auto path = ConvertProprietaryFormat(filePath);

	FileStream fileStream(path, OpenMode::Read_Mode);
	if (!fileStream.IsOpen())
		return false;

	size_t numTexture = 0;
	fileStream.Read(&numTexture);

	Vector<String> texturePaths(numTexture);
	for (auto& path : texturePaths)
	{
		fileStream.Read(&path);
	};

	fileStream.Close();

	if (const auto resoureManager = GetContext()->GetSubsystem<ResourceManager>())
	{
		for (auto& path : texturePaths)
		{
			AddTexture(resoureManager->Load<Texture>(path));
		}
	};

	CreateRootSignature();
	CreatePipelineState();

	return m_textures.empty() == false;
}

void Material::AddTexture(Texture* texture) noexcept
{
	m_textures.emplace_back(texture);
}

void Material::SetVSShader(StringView name)
{
	// ���_���C�A�E�g�쐬
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT"  , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BINORMAL" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	m_VSShader.Compile(name, "main", "vs_5_0");
	m_vertexShader.Create(name, nullptr);
	m_inputLayout.Create(vertexDesc, ARRAYSIZE(vertexDesc), m_vertexShader.GetBlob());
}

void Material::SetPSShader(StringView name)
{
	m_PSShader.Compile(name, "main", "vs_5_0");
	m_pixelShader.Create(name, nullptr);

	// �T���v���[����
	m_samplerState.Create(
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP);
}

void Material::ShaderSet() const noexcept
{
	// ���_�V�F�[�_�[�̃p�����[�^�Z�b�g
	//m_vertexShader.VSSet();
	//
	//// �s�N�Z���V�F�[�_�[�̃p�����[�^�Z�b�g
	//m_pixelShader.PSSet();
	//m_samplerState.PSSet();
	//
	//// ���_���C�A�E�g�̃p�����[�^�Z�b�g
	//m_inputLayout.IASet();
	//
	//// �e�N�X�`���̃p�����[�^�Z�b�g
	//for (int i = 0; i < m_textures.size(); ++i)
	//{
	//	m_textures[i]->PSSet(i);
	//}

	m_rootSignature.SetGraphics();
	m_pipelineState.Set();
}

String Material::ConvertProprietaryFormat(StringView filePath) const noexcept
{
	String path = "assets/Resource/Material/";

	// �t�@�C���g���q��Ǝ��t�@�C���p�ɕύX
	path += FileSystem::GetFilePath(filePath);

	StringView sub(path);
	path = sub.substr(0, sub.find("."));
	path += ".material";

	return path;
}

void Material::CreateRootSignature() noexcept
{
	m_rootSignature.Create(
		D3D12_FILTER_MIN_MAG_MIP_LINEAR,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,
		D3D12_TEXTURE_ADDRESS_MODE_WRAP);
}

void Material::CreatePipelineState() noexcept
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC desc;
	ZeroMemory(&desc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));

	//// ���_���C�A�E�g�쐬
	D3D12_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TANGENT"  , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "BINORMAL" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};
	
	desc.InputLayout.NumElements = _countof(vertexDesc);
	desc.InputLayout.pInputElementDescs = vertexDesc;
	desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	
	desc.VS = CD3DX12_SHADER_BYTECODE(m_VSShader.GetBlob());
	desc.PS = CD3DX12_SHADER_BYTECODE(m_PSShader.GetBlob());
	
	desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;//�J�����O
	desc.RasterizerState.DepthBias = 0.1f;
	desc.RasterizerState.SlopeScaledDepthBias = 0.01f;
	
	//�o��
	desc.NumRenderTargets = 3;//�����_�[�^�[�Q�b�g��
	desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.RTVFormats[1] = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.RTVFormats[2] = DXGI_FORMAT_R8G8B8A8_UNORM;
		
	desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	desc.BlendState.RenderTarget[0].BlendEnable = true;
	desc.BlendState.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	desc.BlendState.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	//SrcBlend=SRC_ALPHA�Ƃ����̂�Src*���Ƃ�������
	desc.BlendState.RenderTarget[0].SrcBlend = D3D12_BLEND_SRC_ALPHA;
	desc.BlendState.RenderTarget[0].DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	desc.BlendState.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	desc.BlendState.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ONE;
	
	//�f�v�X�X�e���V���X�e�[�g
	//���̓f�v�X�Ƃ��g�p���Ȃ�(�\���b�h���f�����ɕK�v)
	desc.DepthStencilState.DepthEnable = true;
	desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	
	desc.DepthStencilState.StencilEnable = false;
	desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
	
	//�S�̓I�Ȑݒ�
	desc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	desc.NodeMask = 0;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
	desc.pRootSignature = m_rootSignature.GetRootSignature();

	m_pipelineState.Create(desc);
}