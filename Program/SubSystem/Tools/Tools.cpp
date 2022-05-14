/**
* @file    Tools.cpp
* @brief   �֗��֐�
*
* @date	   2022/05/06 2022�N�x����
* @author  �ђ˗z��
*/


#include "Tools.h"
#include <Windows.h>

std::wstring ToWstring(std::string_view str) noexcept
{
	// �ϊ���̕�����̒������擾
	int lenght = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str.data(), -1, nullptr, 0);

	std::wstring wstr;
	wstr.reserve(lenght);

	// ������ϊ�
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