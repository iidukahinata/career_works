/**
* @file    FileSystem.cpp
* @brief
*
* @date	   2022/06/27 2022îNìxèâî≈
*/


#include "FileSystem.h"

std::string FileSystem::Canonical(std::string_view file) noexcept
{
	try
	{
		std::filesystem::path buf = std::filesystem::canonical(std::string("./") + file.data());
		return buf.string();
	}
	catch (const std::exception&)
	{
		return std::string();
	}
}

std::string FileSystem::GetFilePath(std::string_view filePath) noexcept
{
	try
	{
		return std::string(filePath.substr(filePath.find_last_of("\\/") + 1, filePath.size()));
	}
	catch (const std::exception&)
	{
		return std::string(filePath);
	}
}