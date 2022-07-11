/**
* @file    Tools.cpp
* @brief   �֗��֐�
*
* @date	   2022/06/25 2022�N�x����
*/


#include <Windows.h>
#include "Tools.h"

Wstring ToWstring(StringView str) noexcept
{
	// �ϊ���̕�����̒������擾
	int lenght = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.data(), -1, nullptr, 0);

	Wstring wstr;
	wstr.reserve(lenght);

	// ������ϊ�
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.data(), -1, &wstr[0], lenght);

	return wstr;
}

String ToString(WstringView str) noexcept
{
	// �ϊ���̕�����̒������擾
	int lenght = WideCharToMultiByte(CP_OEMCP, 0, str.data(), -1, (char*)NULL, 0, NULL, NULL);

	String ret;
	ret.resize(lenght);

	// ������ϊ�
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