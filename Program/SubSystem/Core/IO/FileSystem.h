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

	static String Canonical(String_View filePath) noexcept;

	static String GetFilePath(String_View filePath) noexcept;
};