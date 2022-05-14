/**
* @file    Model.cpp
* @brief
*
* @date	   2022/05/06 2022年度初版
* @author  飯塚陽太
*/


#include "Model.h"
#include <filesystem>
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/ThreadPool/ThreadPool.h"

Model::Model(const Model& model)
{
	this->operator=(model);
}

Model& Model::operator=(const Model& model)
{
	m_vertexShader = model.m_vertexShader;
	m_inputLayout = model.m_inputLayout;
	m_pixelShader = model.m_pixelShader;
	m_samplerState = model.m_samplerState;

	m_modelData = model.m_modelData;
	m_modelData->AddRefreneceCount();

	return *this;
}

Model::~Model()
{
	// 使用しなくなった事を知らせる。
	m_modelData->SubReneceCount();
}

void Model::Init(const ModelDesc& desc)
{
	// 読み込み待ちが起きないよう並列処理で行う
	ThreadPool::Get().AddTask([this, desc]
	{
		if (desc.modelFilePath)
		{
			m_modelData = ResourceManager::Get().Load<ModelData>(desc.modelFilePath);
		}

		if (desc.textureFolderPath)
		{
			LoadTextures(desc.textureFolderPath);
		}
	});

	// 頂点シェーダー生成
	m_vertexShader.Create(desc.vsShader);
	m_inputLayout.Create(desc.layout, desc.layoutSize, m_vertexShader.GetBlob());

	// ピクセルシェーダー生成
	m_pixelShader.Create(desc.psShader);

	// サンプラー生成
	m_samplerState.Create(
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP);
}

void Model::Draw(const DirectX::XMMATRIX& world)
{
	if (!m_modelData)
		return;

	// 頂点シェーダーのパラメータセット
	m_vertexShader.VSSet();

	// ピクセルシェーダーのパラメータセット
	m_pixelShader.PSSet();
	m_samplerState.PSSet();

	// 頂点レイアウトのパラメータセット
	m_inputLayout.IASet();

	// プリミティブタイプをセット
	D3D11GrahicsDevice::Get().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_modelData->Draw(world);
}

void Model::LoadTextures(std::string_view textureFolderPath)
{
	if (!m_modelData)
		return;

	// 指定フォルダ内のデータを取得
	for (const auto& entry : std::filesystem::recursive_directory_iterator(textureFolderPath))
	{
		m_modelData->LoadTexture(entry.path().string().c_str());
	}
}