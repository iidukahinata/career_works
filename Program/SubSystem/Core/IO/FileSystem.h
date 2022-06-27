/**
* @file    FileSystem.h
* @brief
*
* @date	   2022/06/27 2022年度初版
*/
#pragma once


#include <filesystem>

/**
* File用便利関数軍を定義。
* 必要になり次第順序定義し、拡張していく。
*/
class FileSystem
{
public:

	static std::string Canonical(std::string_view filePath) noexcept;

	static std::string GetFilePath(std::string_view filePath) noexcept;
};