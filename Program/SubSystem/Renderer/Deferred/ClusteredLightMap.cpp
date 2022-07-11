/**
* @file    DeferredLightMap.cpp
* @brief
*
* @date	   2022/07/06 2022�N�x����*
* @note
*  �Q�l����
*
*  CEDIL �N���X�^�[�h�V�F�[�f�B���O
*  https://cedil.cesa.or.jp/cedil_sessions/view/1060
*  �Ȃ��ȂɃ��A���^�C�������_�����O
*  https://www.slideshare.net/SatoshiKodaira/ss-69311865
*  �q���[���X-3D
*  http://www.humus.name/index.php?page=3D&ID=90
*/


#include "ClusteredLightMap.h"
#include "SubSystem/Scene/Component/Components/Light.h"
#include "SubSystem/Scene/Component/Components/Camera.h"

void ClusteredLightMap::Initialize()
{
	auto& graphicsDevice = D3D11GraphicsDevice::Get();

	D3D11_TEXTURE3D_DESC desc;
	desc.Width = m_cluster.x;
	desc.Height = m_cluster.y;
	desc.Depth = m_cluster.z;
	desc.MipLevels = 1;
	desc.Format = DXGI_FORMAT_R32G32_UINT;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;

	graphicsDevice.GetDevice()->CreateTexture3D(&desc, nullptr, &m_texture3D);
}

void ClusteredLightMap::Update(Camera* mainCamera)
{
	int pointLightCount = 0;
	int spotLightCount = 0;
	for (int i = 0; i < m_lights.size(); ++i)
	{
		switch (m_lights[i]->GetLightType())
		{
		case LightType::DirectionalLight:
			break;

		case LightType::PointLight:
			PointLightCulling(m_lights[i], pointLightCount);
			++pointLightCount;
			break;

		case LightType::SpotLight:
			SpotLightCulling(m_lights[i], spotLightCount);
			++spotLightCount;
			break;

		default:
			break;
		}
	}

	// Light �f�[�^��GPU���M
	m_texture3D;
}

void ClusteredLightMap::SetAABB(const Math::Vector3& min, const Math::Vector3& max) noexcept
{
	m_aabbMin = min;
	m_aabbMax = max;

	m_scale = (max - min) / m_cluster.ToVector();
	m_invScale = Math::Vector3::One / m_scale;
}

void ClusteredLightMap::PointLightCulling(Light* light, int index) noexcept
{
	const auto range = light->GetInfluenceRange();
	const auto rangeSqr = range * range;

	// AABB��Ԃł̃��C�g�ʒu�擾
	const auto pos = light->GetTransform().GetPosition() - m_aabbMin;

	// �����蔻��̑Ώە������߂邽�߁A�����͂�AABB���擾
	const auto min = (pos - range) * m_invScale;
	const auto max = (pos + range) * m_invScale;

	// ���S���W��Box�ԍ��擾
	const auto centerX = static_cast<int>(pos.x * m_invScale.x);
	const auto centerY = static_cast<int>(pos.y * m_invScale.y);
	const auto centerZ = static_cast<int>(pos.z * m_invScale.z);

	// AABB��Ԃ͈̔͊O�A�N�Z�X��h������ clamp
	const auto minX = std::clamp(static_cast<int>(min.x), 0, m_cluster.x);
	const auto minY = std::clamp(static_cast<int>(min.y), 0, m_cluster.y);
	const auto minZ = std::clamp(static_cast<int>(min.z), 0, m_cluster.z);
	const auto maxX = std::clamp(static_cast<int>(max.x), 0, m_cluster.x);
	const auto maxY = std::clamp(static_cast<int>(max.y), 0, m_cluster.y);
	const auto maxZ = std::clamp(static_cast<int>(max.z), 0, m_cluster.z);

	// �eAABB��ԂƋ��̓����蔻����s��
	for (int z = min.z; z < max.z; ++z)
	{
		float disZ = 0.f;
		if (z != centerZ)
		{
			// Z���ʔԍ�������W�ɕϊ����A���C�g���S���W����̍����擾
			disZ = ((z < centerZ) ? z + 1 : z) * m_invScale.z;
			disZ = disZ - pos.z;
			disZ *= disZ;
		}

		for (int y = min.y; y < max.y; ++y)
		{
			float disY = 0.f;
			if (y != centerY)
			{
				// Y���ʔԍ�������W�ɕϊ����A���C�g���S���W����̍����擾
				disY = ((y < centerY) ? y + 1 : y) * m_invScale.y;
				disY = disY - pos.y;
				disY *= disY;
			}

			float disYZ = disY + disZ;
			for (int x = min.x; x < max.x; ++x)
			{
				float disX = 0.f;
				if (x != centerX)
				{
					// X���ʔԍ�������W�ɕϊ����A���C�g���S���W����̍����擾
					disX = ((x < centerX) ? x + 1 : x) * m_invScale.x;
					disX = disX - pos.x;
					disX *= disX;
				}

				float disXYZ = disX + disYZ;
				if (disXYZ < rangeSqr)
				{
					// �ڐG
					AddPointLightToLightList(x, y, z, index);
				}
			}
		}
	}
}

void ClusteredLightMap::SpotLightCulling(Light* light, int index) noexcept
{

}

void ClusteredLightMap::AddPointLightToLightList(int x, int y, int z, int index) noexcept
{
	m_lightList[0].pointLightIndices.emplace_back(index);
}

void ClusteredLightMap::AddSpotLightToLightList(int x, int y, int z, int index) noexcept
{
	m_lightList[0].spotLightIndices.emplace_back(index);
}