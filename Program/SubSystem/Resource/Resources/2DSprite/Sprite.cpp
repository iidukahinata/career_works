/**
* @file    Sprite.cpp
* @brief
*
* @date	   2022/06/06 2022年度初版
* @author  飯塚陽太
*/


#include "Sprite.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Renderer/Geometry/Plane.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/ThreadPool/ThreadPool.h"

void Sprite::Init(const SpriteDesc& desc)
{
	m_mesh = Plane::Make<Vertex2D>(desc.width, desc.height);

	// 読み込み待ちが起きないよう並列処理で行う
	ThreadPool::Get().AddTask([this, desc]
	{
		// 指定されたPathを優先して追加
		if (!desc.filePath.empty())
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

	//ピクセルシェーダー生成
	m_pixelShader.Create(desc.psShader);

	// サンプラー生成
	m_samplerState.Create();
}

void Sprite::Draw(const DirectX::XMMATRIX& world)
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

	TransformCBuffer::Get().Bind(world);

	m_mesh.Draw();
}