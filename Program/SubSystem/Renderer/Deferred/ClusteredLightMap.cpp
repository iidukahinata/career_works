/**
* @file    DeferredLightMap.cpp
* @brief
*
* @date	   2022/07/13 2022年度初版
* @note
*  参考資料
*
*  CEDIL クラスタードシェーディング
*  https://cedil.cesa.or.jp/cedil_sessions/view/1060
*  なぜなにリアルタイムレンダリング
*  https://www.slideshare.net/SatoshiKodaira/ss-69311865
*  ヒュームス-3D
*  http://www.humus.name/index.php?page=3D&ID=90
*/


#include "ClusteredLightMap.h"
#include "SubSystem/Scene/Component/Components/Light.h"
#include "SubSystem/Scene/Component/Components/Camera.h"

void ClusteredLightMap::Initialize()
{
	m_ambientLight = Math::Vector4(0.5f);

	m_constantBufferLight.Create(sizeof(ConstantBufferLight));
	m_constantBufferLightIndices.Create(sizeof(ConstantBufferLightIndeices));

	// 仮置きで可視性空間を作成。
	Math::Vector3 min = Math::Vector3(-10.f, -5.f, -10.f);
	Math::Vector3 max = Math::Vector3(10.f, 5.f, 10.f);
	SetAABB(min, max);

	// light data 保持用テクスチャ
	D3D11_TEXTURE3D_DESC texture3DDesc;
	texture3DDesc.Width = clusterX;
	texture3DDesc.Height = clusterY;
	texture3DDesc.Depth = clusterZ;
	texture3DDesc.MipLevels = 1;
	texture3DDesc.Format = DXGI_FORMAT_R32G32_UINT;
	texture3DDesc.Usage = D3D11_USAGE_DYNAMIC;
	texture3DDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texture3DDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	texture3DDesc.MiscFlags = 0;
	
	m_texture.Create(&texture3DDesc);
}

void ClusteredLightMap::Update(Camera* mainCamera)
{
	// pre update
	ConstantBufferLight lightBuffer = CreateConstantBufferLight(mainCamera);

	// update buffer
	UpdateLightTexture();
	m_constantBufferLight.Update(lightBuffer);

	// set buffer
	m_constantBufferLight.VSSet(2);
	m_constantBufferLight.PSSet(2);

	m_texture.PSSet(10);
	m_textureLightIndices.PSSet(11);
}

void ClusteredLightMap::SetAABB(const Math::Vector3& min, const Math::Vector3& max) noexcept
{
	m_aabbMin = min;
	m_aabbMax = max;

	m_scale = (max - min) / Math::Vector3(clusterX, clusterY, clusterZ);
	m_invScale = Math::Vector3::One / m_scale;
}

ClusteredLightMap::ConstantBufferLight ClusteredLightMap::CreateConstantBufferLight(const Camera* mainCamera) noexcept
{
	m_lightList.fill(Array<LightList, clusterY, clusterZ>());

	ConstantBufferLight buffer = {};

	int pointLightCount = 0;
	int spotLightCount = 0;

	// 各Light情報を取得し、bufferにセット
	// pointLight、spotLightは最適化のため各カリング処理を追記
	for (auto light : m_lights)
	{
		switch (light->GetLightType())
		{
		case LightType::DirectionalLight:
			buffer.directionalLight.direction = Math::Vector4(light->GetTransform().GetRotation(), 0.f);
			buffer.directionalLight.color = light->GetColor();
			buffer.directionalLight.color.w = light->GetIntensity();
			break;

		case LightType::PointLight:
			PointLightCulling(light, pointLightCount);
			buffer.pointLights[pointLightCount].position = Math::Vector4(light->GetTransform().GetPosition(), 0.f);
			buffer.pointLights[pointLightCount].color = light->GetColor();
			buffer.pointLights[pointLightCount].intensity = light->GetIntensity();
			buffer.pointLights[pointLightCount].influenceRange = light->GetInfluenceRange();
			++pointLightCount;
			break;

		case LightType::SpotLight:
			SpotLightCulling(light, spotLightCount);
			buffer.spotLights[spotLightCount].position = Math::Vector4(light->GetTransform().GetPosition(), 0.f);
			buffer.spotLights[spotLightCount].direction = Math::Vector4(light->GetTransform().GetRotation(), 0.f);
			buffer.spotLights[spotLightCount].color = light->GetColor();
			buffer.spotLights[spotLightCount].intensity = light->GetIntensity();
			buffer.spotLights[spotLightCount].influenceRange = light->GetInfluenceRange();
			buffer.spotLights[spotLightCount].angle = light->GetAngle();
			++spotLightCount;
			break;

		default:
			break;
		}
	}

	// 他Lightデータを設定
	buffer.eyePos = Math::Vector4(mainCamera->GetTransform().GetPosition(), 0);
	buffer.ambientLight = m_ambientLight;
	buffer.pointLightCount = pointLightCount;
	buffer.spotLightCount = spotLightCount;
	buffer.invScale = Math::Vector4(m_invScale, 0.f);
	buffer.bias = Math::Vector4(-m_invScale * m_aabbMin, 0.f);

	return buffer;
}

void ClusteredLightMap::UpdateLightTexture() noexcept
{
	struct LightStruct
	{
		uint32_t offset;
		uint16_t pointLightCount;
		uint16_t spotLightCount;
	};

	const auto context = D3D11GraphicsDevice::Get().GetContext();

	// Light データをGPU送信
	D3D11_MAPPED_SUBRESOURCE pLightData;
	HRESULT hr = context->Map(m_texture.GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pLightData);
	if (FAILED(hr))
	{
		return;
	}

	// テクスチャ更新データ保存用一時変数
	int indicesOffset = 0;
	Array<LightStruct, clusterX> lightData = {};
	ConstantBufferLightIndeices lightIndices = {};

	for (int z = 0; z < clusterZ; ++z)
	{
		for (int y = 0; y < clusterY; ++y)
		{
			for (int x = 0; x < clusterX; ++x)
			{
				auto pointIndices = m_lightList[z][y][x].pointLightIndices;
				auto spotIndices = m_lightList[z][y][x].spotLightIndices;

				// テクスチャデータ用
				lightData[x].offset = indicesOffset;
				lightData[x].pointLightCount = pointIndices.size();
				lightData[x].spotLightCount = spotIndices.size();

				// buffer データ追加
				for (auto& pointIndex : pointIndices)
				{
					if (indicesOffset < 4096)
					{
						lightIndices.lightIndices[indicesOffset] = pointIndex;
					}
					++indicesOffset;
				}

				for (auto& spotIndex : spotIndices)
				{
					lightIndices.lightIndices[indicesOffset] = spotIndex;
					++indicesOffset;
				}
			}
			
			const int size = clusterX * clusterY * clusterZ * 16;
			void* data = ((uint8_t*)(pLightData.pData)) + (z * pLightData.DepthPitch) + (y * pLightData.RowPitch);
			memcpy_s(data, size, lightData.data(), sizeof(LightStruct) * clusterX);
		}
	}

	context->Unmap(m_texture.GetResource(), 0);

	m_constantBufferLightIndices.Update(lightIndices);
}

void ClusteredLightMap::PointLightCulling(Light* light, const uint32_t index) noexcept
{
	const auto range = light->GetInfluenceRange();
	const auto rangeSqr = range * range;

	// AABB空間でのライト位置取得
	const auto pos = light->GetTransform().GetPosition() - m_aabbMin;

	// 当たり判定の対象物を求めるため、球を囲うAABBを取得
	const auto min = (pos - range) * m_invScale;
	const auto max = (pos + range) * m_invScale;

	// 中心座標のBox番号取得
	const auto centerX = static_cast<int>(floorf(pos.x * m_invScale.x));
	const auto centerY = static_cast<int>(floorf(pos.y * m_invScale.y));
	const auto centerZ = static_cast<int>(floorf(pos.z * m_invScale.z));

	// AABB空間の範囲外アクセスを防ぐため clamp
	const auto minX = std::clamp(static_cast<int>(floorf(min.x)), 0, clusterX);
	const auto minY = std::clamp(static_cast<int>(floorf(min.y)), 0, clusterY);
	const auto minZ = std::clamp(static_cast<int>(floorf(min.z)), 0, clusterZ);
	const auto maxX = std::clamp(static_cast<int>(ceilf(max.x)), 0, clusterX);
	const auto maxY = std::clamp(static_cast<int>(ceilf(max.y)), 0, clusterY);
	const auto maxZ = std::clamp(static_cast<int>(ceilf(max.z)), 0, clusterZ);

	// AABBと球との当たり判定から pointLight が影響するピクセルを抽出
	for (uint32_t z = minZ; z < maxZ; ++z)
	{
		float disZ = 0.f;
		if (z != centerZ)
		{
			// Z平面番号から座標に変換し、ライト中心座標からの差を取得
			disZ = ((z <= centerZ) ? z + 1 : z) * m_scale.z;
			disZ += m_aabbMin.z - light->GetTransform().GetPosition().z;
			disZ *= disZ;
		}

		for (uint32_t y = minY; y < maxY; ++y)
		{
			float disY = 0.f;
			if (y != centerY)
			{
				// Y平面番号から座標に変換し、ライト中心座標からの差を取得
				disY = ((y <= centerY) ? y + 1 : y) * m_scale.y;
				disY += m_aabbMin.y - light->GetTransform().GetPosition().y;
				disY *= disY;
			}

			const float disYZ = disY + disZ;
			for (uint32_t x = minX; x < maxX; ++x)
			{
				float disX = 0.f;
				if (x != centerX)
				{
					// X平面番号から座標に変換し、ライト中心座標からの差を取得
					disX = ((x <= centerX) ? x + 1 : x) * m_scale.x;
					disX += m_aabbMin.x - light->GetTransform().GetPosition().x;
					disX *= disX;
				}

				const float disXYZ = disX + disYZ;
				if (disXYZ < rangeSqr)
				{
					AddPointLightToLightList(x, y, z, index);
				}
			}
		}
	}
}

void ClusteredLightMap::SpotLightCulling(Light* light, const uint32_t index) noexcept
{

}

void ClusteredLightMap::AddPointLightToLightList(const uint32_t x, const uint32_t y, const uint32_t z, const uint32_t index) noexcept
{
	m_lightList[x][y][z].pointLightIndices.emplace_back(index);
}

void ClusteredLightMap::AddSpotLightToLightList(const uint32_t x, const uint32_t y, const uint32_t z, const uint32_t index) noexcept
{
	m_lightList[x][y][z].spotLightIndices.emplace_back(index);
}