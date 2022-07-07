/**
* @file	   LightMap.cpp
* @brief   Light�Ǘ��N���X
*
* @date	   2022/07/08 2022�N�x����
*/


#include "LightMap.h"
#include "SubSystem/Scene/Component/Components/Light.h"

LightMap::~LightMap()
{
	Clear();
}

void LightMap::Clear() noexcept
{
	m_lights.clear();
	m_lights.shrink_to_fit();
}

void LightMap::AddLight(Light* light) noexcept
{
	m_lights.push_back(light);
}

void LightMap::RemoveLight(Light* light) noexcept
{
	for (auto it = m_lights.begin(); it != m_lights.end(); it++)
	{
		if (*it == light)
		{
			m_lights.erase(it);
			break;
		}
	}
}

void LightMap::SetAmbient(const Math::Vector4& ambientLight) noexcept
{
	m_ambientLight = ambientLight;
}