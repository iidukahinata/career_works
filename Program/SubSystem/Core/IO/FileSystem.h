/**
* @file    FileSystem.h
* @brief
*
* @date	   2022/06/27 2022�N�x����
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

	static std::string Canonical(std::string_view filePath) noexcept;

	static std::string GetFilePath(std::string_view filePath) noexcept;
};