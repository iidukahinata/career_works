/**
* @file    Material.cpp
* @brief
*
* @date	   2022/07/06 2022年度初版
*/


#include "Material.h"
#include "SubSystem/Core/Context.h"
#include "SubSystem/Core/IO/FileStream.h"
#include "SubSystem/Core/IO/FileSystem.h"
#include "SubSystem/Resource/ResourceManager.h"

Material::Material()
{
	// 仮設定
	SetVSShader("assets/Resource/Shader/PBR_VS.cso");
	SetPSShader("assets/Resource/Shader/PBR_PS.cso");

	// サンプラー生成
	m_samplerState.Create(
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP);
}

void Material::SaveToFile(String_View filePath)
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

bool Material::LoadFromFile(String_View filePath)
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

	return m_textures.empty() == false;
}

void Material::AddTexture(Texture* texture) noexcept
{
	m_textures.emplace_back(texture);
}

void Material::SetVSShader(String_View name)
{
	// 頂点レイアウト作成
	D3D11_INPUT_ELEMENT_DESC vertexDesc[] = {
		{ "POSITION" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, 0					    	 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD" , 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"   , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT"  , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "BINORMAL" , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	m_vertexShader.Create(name, nullptr);
	m_inputLayout.Create(vertexDesc, ARRAYSIZE(vertexDesc), m_vertexShader.GetBlob());
}

void Material::SetPSShader(String_View name)
{
	m_pixelShader.Create(name, nullptr);
}

void Material::ShaderSet() noexcept
{
	// 頂点シェーダーのパラメータセット
	m_vertexShader.VSSet();

	// ピクセルシェーダーのパラメータセット
	m_pixelShader.PSSet();
	m_samplerState.PSSet();

	// 頂点レイアウトのパラメータセット
	m_inputLayout.IASet();

	// テクスチャのパラメータセット
	for (int i = 0; i < m_textures.size(); ++i)
	{
		m_textures[i]->PSSet(i);
	}
}

String Material::ConvertProprietaryFormat(String_View filePath) const noexcept
{
	String path = "assets/Resource/Material/";

	// ファイル拡張子を独自ファイル用に変更
	path += FileSystem::GetFilePath(filePath);

	String_View sub(path);
	path = sub.substr(0, sub.find("."));
	path += ".material";

	return path;
}