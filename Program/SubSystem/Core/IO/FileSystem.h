#pragma once


#include <filesystem>

class FileSystem
{
public:

	static std::string_view Canonical(std::string_view file) noexcept;
};