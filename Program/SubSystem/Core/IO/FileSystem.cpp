/**
* @file    FileSystem.cpp
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/


#include "FileSystem.h"

String FileSystem::Canonical(StringView file) noexcept
{
	try
	{
		std::filesystem::path buf = std::filesystem::canonical(String("./") + file.data());
		return buf.string().c_str();
	}
	catch (const std::exception&)
	{
		return String();
	}
}

String FileSystem::GetFilePath(StringView filePath) noexcept
{
	try
	{
		return String(filePath.substr(filePath.find_last_of("\\/") + 1, filePath.size()));
	}
	catch (const std::exception&)
	{
		return String(filePath);
	}
}