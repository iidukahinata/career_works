/**
* @file    IResource.cpp
* @brief   リソース抽象クラス
*
* @date	   2022/07/06 2022年度初版
*/


#include "IResource.h"

extern Context* g_context;

void IResource::SaveToFile(String_View filePath)
{

}

bool IResource::LoadFromFile(String_View filePath)
{
	return false;
}

bool IResource::Load(String_View filePath) noexcept
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