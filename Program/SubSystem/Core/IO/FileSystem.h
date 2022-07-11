/**
* @file    FileSystem.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include <filesystem>

/**
* File�p�֗��֐��R���`�B
* �K�v�ɂȂ莟�揇����`���A�g�����Ă����B
*/
class FileSystem
{
public:

	static String Canonical(StringView filePath) noexcept;

	static String GetFilePath(StringView filePath) noexcept;
};