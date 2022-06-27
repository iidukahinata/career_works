/**
* @file    Material.cpp
* @brief
*
* @date	   2022/06/27 2022�N�x����
*/


#include "Material.h"
#include "SubSystem/Core/IO/FileStream.h"
#include "SubSystem/Core/IO/FileSystem.h"
#include "SubSystem/Resource/ResourceManager.h"

Material::Material()
{
	// ���ݒ�
	SetVSShader("assets/Shader/PBR_VS.cso");
	SetPSShader("assets/Shader/PBR_PS.cso");

	// �T���v���[����
	m_samplerState.Create(
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP);
}

void Material::SaveToFile(std::string_view filePath)
{
	if (m_textures.size() == 0)
		return;

	auto path = ConvertProprietaryFormat(filePath);

	FileStream fileStream;
	if (!fileStream.CreateFileAndLoad(path, OpenMode::Write_Mode))
		return;

	fileStream.Write(m_textures.size());
	for (auto& texture : m_textures)
	{
		fileStream.Write(texture->GetName());
	};
}

bool Material::LoadFromFile(std::string_view filePath)
{
	auto path = ConvertProprietaryFormat(filePath);

	FileStream fileStream(path, OpenMode::Read_Mode);
	if (!fileStream.IsOpen())
		return false;

	size_t numTexture = 0;
	fileStream.Read(&numTexture);

	std::vector<std::string> texturePaths(numTexture);
	for (auto& path : texturePaths)
	{
		fileStream.Read(&path);
	};

	auto resoureManager = GetContext()->GetSubsystem<ResourceManager>();
	for (auto& path : texturePaths)
	{
		AddTexture(resoureManager->Load<Texture>(path));
	}

	return m_textures.empty() == false;
}

void Material::AddTexture(Texture* texture) noexcept
{
	m_textures.emplace_back(texture);
}

void Material::SetVSShader(std::string_view name)
{
	// ���_���C�A�E�g�쐬
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT"  , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BINORMAL" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	m_vertexShader.Create(name);
	m_inputLayout.Create(vertexDesc, ARRAYSIZE(vertexDesc), m_vertexShader.GetBlob());
}

void Material::SetPSShader(std::string_view name)
{
	m_pixelShader.Create(name);
}

void Material::ShaderSet() noexcept
{
	// ���_�V�F�[�_�[�̃p�����[�^�Z�b�g
	m_vertexShader.VSSet();

	// �s�N�Z���V�F�[�_�[�̃p�����[�^�Z�b�g
	m_pixelShader.PSSet();
	m_samplerState.PSSet();

	// ���_���C�A�E�g�̃p�����[�^�Z�b�g
	m_inputLayout.IASet();

	// �e�N�X�`���̃p�����[�^�Z�b�g
	for (int i = 0; i < m_textures.size(); ++i)
	{
		m_textures[i]->PSSet(i);
	}
}

std::string Material::ConvertProprietaryFormat(std::string_view filePath) const noexcept
{
	std::string path = "assets/Resource/Material/";

	// �t�@�C���g���q��Ǝ��t�@�C���p�ɕύX
	path += FileSystem::GetFilePath(filePath);

	std::string_view sub(path);
	path = sub.substr(0, sub.find("."));
	path += ".material";

	return path;
}