/**
* @file    FileStream.cpp
* @brief   �t�@�C������N���X
*
* @data	   2022/06/06 2022�N�x����
* @author  �ђ˗z��
*/


#include "FileStream.h"
#include "SubSystem/Log/DebugLog.h"

#ifdef USE_C_VERSION
#include <errno.h>

FileStream::FileStream(std::string_view filePath, OpenMode mode)
{
	Load(filePath, mode);
}

FileStream::~FileStream()
{
	Close();
}

bool FileStream::Load(std::string_view filePath, OpenMode mode) noexcept
{
	if (IsOpen())
	{
		Close();
	}

	m_openMode = mode;

	errno_t error = 0;
	switch (m_openMode)
	{
	case OpenMode::Txt_Mode:
		error = fopen_s(&m_fp, filePath.data(), "w+");
		break;
	case OpenMode::Read_Mode:
		error = fopen_s(&m_fp, filePath.data(), "rb");
		break;
	case OpenMode::Write_Mode:
		error = fopen_s(&m_fp, filePath.data(), "wb");
		break;
	}

	if (error != 0)
	{
		// �J���Ȃ��������Ƃ� �߂�l�Ŕ��f�o���邽�ߊO���B
		if(error != 2)
		{
			std::string buf;
			buf.resize(128);
			strerror_s(buf.data(), buf.size(), static_cast<int>(error));
			LOG_ERROR("error :" + std::string(buf));
		}

		m_openMode = OpenMode::Not_Mode;
		m_fp = nullptr;
	}

	return IsOpen();
}

bool FileStream::CreateFile(std::string_view filePath, OpenMode mode) noexcept
{
	FILE* fp = nullptr;
	errno_t error = 0;

	switch (mode)
	{
	case OpenMode::Txt_Mode:
		error = fopen_s(&m_fp, filePath.data(), "w");
		break;
	case OpenMode::Read_Mode:
	case OpenMode::Write_Mode:
		error = fopen_s(&m_fp, filePath.data(), "wb");
		break;
	}

	if (error == 0)
	{
		// �t�@�C���̍쐬�ɐ���
		if (fp) fclose(fp);
		return true;
	}

	std::string buf;
	buf.resize(128);
	strerror_s(buf.data(), buf.size(), static_cast<int>(error));
	LOG_ERROR("error :" + std::string(buf));
	return false;
}

bool FileStream::CreateFileAndLoad(std::string_view filePath, OpenMode mode) noexcept
{
	if (CreateFile(filePath, mode))
	{
		return Load(filePath, mode);
	}
	return false;
}

void FileStream::Close() noexcept
{
	if (!IsOpen())
		return;

	fclose(m_fp);

	m_fp = nullptr;
	m_openMode = OpenMode::Not_Mode;
}

bool FileStream::IsOpen() const noexcept
{ 
	return m_fp;
}

bool FileStream::IsEof() const noexcept
{
	return feof(m_fp) != 0;
}
#else
FileStream::FileStream(std::string_view filePath, OpenMode mode)
{
	Load(filePath, mode);
}

FileStream::~FileStream()
{
	Close();
}

bool FileStream::Load(std::string_view filePath, OpenMode mode) noexcept
{
	if (IsOpen())
	{
		Close();
	}

	m_openMode = mode;

	switch (m_openMode)
	{
	case OpenMode::Txt_Mode:
		m_fp.open(filePath.data());
		break;
	case OpenMode::Read_Mode:
		m_fp.open(filePath.data(), std::ios::binary | std::ios::in);
		break;
	case OpenMode::Write_Mode:
		m_fp.open(filePath.data(), std::ios::binary | std::ios::out);
		break;
	}

	return IsOpen();
}

bool FileStream::CreateFile(std::string_view filePath, OpenMode mode) noexcept
{
	std::ofstream createFile;

	switch (mode)
	{
	case OpenMode::Txt_Mode:
		createFile.open(filePath.data(), std::ios::out);
		break;
	case OpenMode::Read_Mode:
	case OpenMode::Write_Mode:
		createFile.open(filePath.data(), (std::ios::out | std::ios::binary));
		break;
	}

	if (createFile.is_open())
	{
		// �t�@�C���̍쐬�ɐ���
		createFile.close();
		return true;
	}
	return false;
}

bool FileStream::CreateFileAndLoad(std::string_view filePath, OpenMode mode) noexcept
{
	if (CreateFile(filePath, mode))
	{
		return Load(filePath, mode);
	}
	return false;
}

void FileStream::Close() noexcept
{
	if (!IsOpen())
		return;

	switch (m_openMode)
	{
	case OpenMode::Txt_Mode:
		break;
	case OpenMode::Read_Mode:
		m_fp.clear();
		break;
	case OpenMode::Write_Mode:
		m_fp.flush();
		break;
	default:
		break;
	}

	m_fp.close();
	m_openMode = OpenMode::Not_Mode;
}
#endif // USE_C