#include "FileSystem.h"

std::string_view FileSystem::Canonical(std::string_view file) noexcept
{
	try
	{
		std::filesystem::path buf = std::filesystem::canonical(std::string("./") + file.data());
		return buf.string().c_str();
	}
	catch (const std::exception&)
	{
		return std::string_view();
	}
}