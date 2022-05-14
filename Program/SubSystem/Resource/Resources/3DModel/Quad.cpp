/**
* @file    Quad.cpp
* @brief
*
* @date	   2022/05/01 2022年度初版
* @author  飯塚陽太
*/


#include "Quad.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Renderer/Geometry/Plane.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/ThreadPool/ThreadPool.h"

Quad::Quad() : 
	m_color(1, 1, 1, 1)
{}

void Quad::Init(const QuadDesc& desc)
{
	m_mesh = Plane::Make<Vertex3D>();

	// 読み込み待ちが起きないよう並列処理で行う
	ThreadPool::Get().AddTask([this, desc]
	{
		// 指定されたPathを優先して追加
		if (desc.filePath)
		{
			m_mesh.AddTexture(ResourceManager::Get().Load<D3D11Texture>(desc.filePath));
		}

		// 読み込まれているデータがある時のみ処理
		for (auto texture : desc.textures)
		{
			m_mesh.AddTexture(texture);
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

void Quad::Draw(const DirectX::XMMATRIX& world)
{
	// 頂点シェーダーのパラメータセット
	m_vertexShader.VSSet();

	// ピクセルシェーダーのパラメータセット
	m_pixelShader.PSSet();
	m_samplerState.PSSet();

	// 頂点レイアウトのパラメータセット
	m_inputLayout.IASet();

	// プリミティブタイプをセット
	D3D11GrahicsDevice::Get().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	TransformCBuffer::Get().Bind(world, m_color);

	m_mesh.Draw();
}