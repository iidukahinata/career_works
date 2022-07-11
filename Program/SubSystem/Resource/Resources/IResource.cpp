/**
* @file    IResource.cpp
* @brief   ���\�[�X���ۃN���X
*
* @date	   2022/07/06 2022�N�x����
*/


#include "IResource.h"

extern Context* g_context;

void IResource::SaveToFile(StringView filePath)
{

}

bool IResource::LoadFromFile(StringView filePath)
{
	return false;
}

bool IResource::Load(StringView filePath) noexcept
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

const String& IResource::GetName() const noexcept
{
	return m_filePath;
}

Context* IResource::GetContext() const noexcept
{
	return g_context;
}