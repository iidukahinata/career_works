/**
* @file    FileSystem.h
* @brief
*
* @date	   2022/07/06 2022年度初版
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

	static String Canonical(StringView filePath) noexcept;

	static String GetFilePath(StringView filePath) noexcept;
};