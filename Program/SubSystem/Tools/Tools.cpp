/**
* @file    Tools.cpp
* @brief   •Ö—˜ŠÖ”
*
* @date	   2022/05/06 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/


#include "Tools.h"
#include <Windows.h>

std::wstring ToWstring(std::string_view str) noexcept
{
	// •ÏŠ·Œã‚Ì•¶š—ñ‚Ì’·‚³‚ğæ“¾
	int lenght = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.data(), -1, nullptr, 0);

	std::wstring wstr;
	wstr.reserve(lenght);

	// •¶š—ñ•ÏŠ·
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.data(), -1, &wstr[0], lenght);

	return wstr;
}

std::string GetExt(std::string_view filePath) noexcept
{
	if (filePath.empty())
	{
		return std::string();
	}

	auto ext_i = filePath.find_last_of(".");
	if (ext_i == std::string::npos) 
	{
		return std::string();
	}

	return std::string(filePath.substr(ext_i + 1, filePath.size() - ext_i));
}