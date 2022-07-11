/**
* @file    Tools.cpp
* @brief   •Ö—˜ŠÖ”
*
* @date	   2022/06/25 2022”N“x‰”Å
*/


#include <Windows.h>
#include "Tools.h"

Wstring ToWstring(StringView str) noexcept
{
	// •ÏŠ·Œã‚Ì•¶š—ñ‚Ì’·‚³‚ğæ“¾
	int lenght = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.data(), -1, nullptr, 0);

	Wstring wstr;
	wstr.reserve(lenght);

	// •¶š—ñ•ÏŠ·
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.data(), -1, &wstr[0], lenght);

	return wstr;
}

String ToString(WstringView str) noexcept
{
	// •ÏŠ·Œã‚Ì•¶š—ñ‚Ì’·‚³‚ğæ“¾
	int lenght = WideCharToMultiByte(CP_OEMCP, 0, str.data(), -1, (char*)NULL, 0, NULL, NULL);

	String ret;
	ret.resize(lenght);

	// •¶š—ñ•ÏŠ·
	WideCharToMultiByte(CP_OEMCP, 0, str.data(), -1, ret.data(), lenght, NULL, NULL);

	return ret;
}

String GetExt(StringView filePath) noexcept
{
	auto ext_i = filePath.find_last_of(".");
	if (ext_i == StringView::npos)
	{
		return String();
	}

	return String(filePath.substr(ext_i + 1, filePath.size() - ext_i));
}