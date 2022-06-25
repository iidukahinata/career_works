/**
* @file    Tools.cpp
* @brief   •Ö—˜ŠÖ”
*
* @date	   2022/05/28 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/


#include <Windows.h>
#include "Tools.h"

std::wstring_view ToWstring(std::string_view str) noexcept
{
	// •ÏŠ·Œã‚Ì•¶š—ñ‚Ì’·‚³‚ğæ“¾
	int lenght = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.data(), -1, nullptr, 0);

	std::wstring wstr;
	wstr.reserve(lenght);

	// •¶š—ñ•ÏŠ·
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.data(), -1, &wstr[0], lenght);

	return wstr;
}

std::string_view ToString(std::wstring_view str) noexcept
{
	// •ÏŠ·Œã‚Ì•¶š—ñ‚Ì’·‚³‚ğæ“¾
	int lenght = WideCharToMultiByte(CP_OEMCP, 0, str.data(), -1, (char*)NULL, 0, NULL, NULL);

	std::string ret;
	ret.resize(lenght);

	// •¶š—ñ•ÏŠ·
	WideCharToMultiByte(CP_OEMCP, 0, str.data(), -1, ret.data(), lenght, NULL, NULL);

	return ret;
}

std::string_view GetExt(std::string_view filePath) noexcept
{
	auto ext_i = filePath.find_last_of(".");
	if (ext_i == std::string_view::npos)
	{
		return std::string_view();
	}

	return std::string_view(filePath.substr(ext_i + 1, filePath.size() - ext_i));
}