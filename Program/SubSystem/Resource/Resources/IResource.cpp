/**
* @file    IResource.cpp
* @brief   ���\�[�X���ۃN���X
*
* @date	   2022/06/25 2022�N�x����
*/


#include "IResource.h"

void IResource::SaveToFile(std::string_view filePath)
{
}

bool IResource::LoadFromFile(std::string_view filePath)
{
	return false;
}

bool IResource::Load(std::string_view filePath) noexcept
{
	m_filePath = filePath;

	if (LoadFromFile(filePath))
	{
		return true;
	}

	if (Do_Load(filePath))
	{
		SaveToFile(filePath);
		return true;
	}
	return false;
}

std::string_view IResource::GetName() const noexcept
{
	return m_filePath;
}

void IResource::AddRef() noexcept
{
	++m_referenceCount;
}

void IResource::SubRef() noexcept
{
	--m_referenceCount;
}

size_t IResource::GetRef() const noexcept
{
	return m_referenceCount;
}