/**
* @file    FileStream.h
* @brief   ファイル操作クラス
*
* @data	   2022/06/06 2022年度初版
* @author  飯塚陽太
* @note
*  書き読み込み速度向上のため c 言語での処理に修正。
*  fscanf 操作関数は作成していません。
*  c++ での処理は c 言語での処理の下に残しておく。
*/
#pragma once


#include <fstream>
#include <vector>
#include <string>

#define USE_C_VERSION

enum class OpenMode
{
	Txt_Mode,
	Read_Mode,
	Write_Mode,
	Not_Mode,
};

#ifdef USE_C_VERSION

class FileStream
{
public:

	FileStream() = default;

	FileStream(std::string_view filePath, OpenMode mode);

	FileStream(const FileStream&) = delete;
	FileStream& operator=(const FileStream&) = delete;

	~FileStream();

	bool Load(std::string_view filePath, OpenMode mode) noexcept;

	/** もし同じ名前のFileがある場合はデータを上書きして作成する。*/
	bool CreateFile(std::string_view filePath, OpenMode mode) noexcept;

	/** もし同じ名前のFileがある場合はデータを上書きして作成する。*/
	bool CreateFileAndLoad(std::string_view filePath, OpenMode mode) noexcept;

	/**
	* 指定型 T データサイズ分書き込みます。
	* string 型はOpenMode によって内部実装が変わるため特殊化されています。
	* 通常の配列、文字列を使用する場合は、他のオーバーロード関数を使用してください。
	*/
	template<class T>
	void Write(T data) noexcept;

	/**
	* 指定されたサイズ分のデータのみをファイルに書き込みます。
	* そのため、次回使用するためには別途サイズを記録しておく必要があります。
	*/
	template<class T>
	void Write(T* data, const size_t& size) noexcept;

	/**
	* 次回呼び出すために使用される要素数も記録されます。
	* string 型はOpenMode によって内部実装が変わるため特殊化されています。
	*/
	template<class T>
	void Write(std::vector<T> data) noexcept;

	/**
	* 指定型 T データサイズ分読み込みます。
	* string 型は OpenMode によって処理が違うため特殊化されています。
	* 通常の配列、文字列を使用する場合は、他のオーバーロード関数を使用してください。
	*/
	template<class T>
	void Read(T* data) noexcept;

	/** 指定されたサイズ分のデータをファイルから取得します。*/
	template<class T>
	void Read(T* data, const size_t& size) noexcept;

	/**
	* データ読み込み前に要素数が取得、確保され読み込まれます。
	* string 型は OpenMode によって処理が違うため特殊化されています。
	*/
	template<class T>
	void Read(std::vector<T>* data) noexcept;

	void Close() noexcept;

	bool IsOpen() const noexcept;
	bool IsEof() const noexcept;

private:

	// * file data
	FILE* m_fp = nullptr;

	OpenMode m_openMode = OpenMode::Not_Mode;
};

template<class T>
inline void FileStream::Write(T data) noexcept
{
	if (m_openMode != OpenMode::Write_Mode)
		return;

	fwrite(reinterpret_cast<void*>(&data), sizeof(T), 1, m_fp);
}

template<>
inline void FileStream::Write(std::string data) noexcept
{
	if (m_openMode == OpenMode::Txt_Mode)
	{
		fputs(data.data(), m_fp);
	}
	else if (m_openMode == OpenMode::Write_Mode)
	{
		size_t length = data.length();
		fwrite(reinterpret_cast<void*>(&length), sizeof(size_t), 1, m_fp);
		fwrite(reinterpret_cast<void*>(data.data()), length, 1, m_fp);
	}
}

template<class T>
inline void FileStream::Write(T* data, const size_t& size) noexcept
{
	if (m_openMode != OpenMode::Write_Mode)
		return;

	fwrite(reinterpret_cast<void*>(data), size, 1, m_fp);
}

template<class T>
inline void FileStream::Write(std::vector<T> data) noexcept
{
	if (m_openMode != OpenMode::Write_Mode)
		return;

	size_t size = data.size();
	fwrite(reinterpret_cast<void*>(&size), sizeof(size_t), 1, m_fp);
	fwrite(reinterpret_cast<void*>(data.data()), sizeof(T), size, m_fp);
}

template<>
inline void FileStream::Write<std::string>(std::vector<std::string> data) noexcept
{
	if (m_openMode == OpenMode::Txt_Mode)
	{
		for (const auto& addText : data)
		{
			fputs(addText.data(), m_fp);
		}
	}
	else if (m_openMode == OpenMode::Write_Mode)
	{
		size_t size = data.size();
		fwrite(reinterpret_cast<void*>(&size), sizeof(size_t), 1, m_fp);

		for (int i = 0; i < size; ++i)
		{
			size_t length = data[i].length();
			fwrite(reinterpret_cast<void*>(&length), sizeof(size_t), 1, m_fp);
			fwrite(reinterpret_cast<void*>(data[i].data()), length, 1, m_fp);
		}
	}
}

template<class T>
inline void FileStream::Read(T* data) noexcept
{
	if (m_openMode != OpenMode::Read_Mode)
		return;

	size_t size = sizeof(T);
	fread(reinterpret_cast<void*>(data), sizeof(T), 1, m_fp);
}

template<>
inline void FileStream::Read<std::string>(std::string* data) noexcept
{
	if (m_openMode == OpenMode::Txt_Mode)
	{
		// 終端チェック
		if (IsEof())
			return;

		char buf[256];
		fgets(buf, 256, m_fp);
		*data = buf;
	}
	else if (m_openMode == OpenMode::Read_Mode)
	{
		size_t length;
		fread(reinterpret_cast<void*>(&length), sizeof(size_t), 1, m_fp);

		data->resize(length);
		fread(reinterpret_cast<void*>(data->data()), length, 1, m_fp);
	}
}

template<class T>
inline void FileStream::Read(T* data, const size_t& size) noexcept
{
	if (m_openMode != OpenMode::Read_Mode)
		return;

	fread(reinterpret_cast<void*>(data), size, 1, m_fp);
}

template<class T>
inline void FileStream::Read(std::vector<T>* data) noexcept
{
	if (m_openMode != OpenMode::Read_Mode)
		return;

	size_t size;
	fread(reinterpret_cast<void*>(&size), sizeof(size_t), 1, m_fp);

	data->resize(size);
	fread(reinterpret_cast<void*>(data->data()), sizeof(T), size, m_fp);
}

template<>
inline void FileStream::Read<std::string>(std::vector<std::string>* data) noexcept
{
	if (m_openMode == OpenMode::Txt_Mode)
	{
		/** ファイルの先頭から全てのデータを読み込む */
		if (fseek(m_fp, 0L, SEEK_SET) != 0)
			return;

		// 終端チェック
		while (!IsEof())
		{
			char buf[256];
			fgets(buf, 256, m_fp);
			data->push_back(std::move(buf));
		}
	}
	else if (m_openMode == OpenMode::Read_Mode)
	{
		size_t size;
		fread(reinterpret_cast<void*>(&size), sizeof(size_t), 1, m_fp);

		data->resize(size);
		for (int i = 0; i < size; ++i)
		{
			size_t length;
			fread(reinterpret_cast<void*>(&length), sizeof(size_t), 1, m_fp);

			data[i].resize(length);
			fread(reinterpret_cast<void*>(data->at(i).data()), length, 1, m_fp);
		}
	}
}

#else

class FileStream
{
public:

	FileStream() = default;

	FileStream(std::string_view filePath, OpenMode mode);

	FileStream(const FileStream&) = delete;
	FileStream& operator=(const FileStream&) = delete;

	~FileStream();

	bool Load(std::string_view filePath, OpenMode mode) noexcept;

	/** もし同じ名前のFileがある場合はデータを上書きして作成する。*/
	bool CreateFile(std::string_view filePath, OpenMode mode) noexcept;

	/** もし同じ名前のFileがある場合はデータを上書きして作成する。*/
	bool CreateFileAndLoad(std::string_view filePath, OpenMode mode) noexcept;

	/**
	* 指定型 T データサイズ分書き込みます。
	* string 型はOpenMode によって内部実装が変わるため特殊化されています。
	* 通常の配列、文字列を使用する場合は、他のオーバーロード関数を使用してください。
	*/
	template<class T>
	void Write(T data) noexcept;

	/**
	* 指定されたサイズ分のデータのみをファイルに書き込みます。
	* そのため、次回使用するためには別途サイズを記録しておく必要があります。
	*/
	template<class T>
	void Write(T* data, const size_t& size) noexcept;

	/**
	* 次回呼び出すために使用される要素数も記録されます。
	* string 型はOpenMode によって内部実装が変わるため特殊化されています。
	*/
	template<class T>
	void Write(std::vector<T> data) noexcept;

	/**
	* 指定型 T データサイズ分読み込みます。
	* string 型は OpenMode によって処理が違うため特殊化されています。
	* 通常の配列、文字列を使用する場合は、他のオーバーロード関数を使用してください。
	*/
	template<class T>
	void Read(T* data) noexcept;

	/** 指定されたサイズ分のデータをファイルから取得します。*/
	template<class T>
	void Read(T* data, const size_t& size) noexcept;

	/**
	* データ読み込み前に要素数が取得、確保され読み込まれます。
	* string 型は OpenMode によって処理が違うため特殊化されています。
	*/
	template<class T>
	void Read(std::vector<T>* data) noexcept;

	void Close() noexcept;

	bool IsOpen() const noexcept { return m_fp.is_open(); }
	bool IsEof() const noexcept { return m_fp.eof(); }

private:

	// * file data
	std::fstream m_fp;

	OpenMode m_openMode = OpenMode::Not_Mode;
};

template<class T>
inline void FileStream::Write(T data) noexcept
{
	if (m_openMode != OpenMode::Write_Mode)
		return;

	m_fp.write(reinterpret_cast<char*>(&data), sizeof(T));
}

template<>
inline void FileStream::Write<std::string>(std::string data) noexcept
{
	if (m_openMode == OpenMode::Txt_Mode)
	{
		m_fp.clear();
		m_fp << data.data();
	}
	else if (m_openMode == OpenMode::Write_Mode)
	{
		m_fp.write(reinterpret_cast<char*>(data.length()), sizeof(size_t));
		m_fp.write(const_cast<char*>(data.data()), data.length());
	}
}

template<class T>
inline void FileStream::Write(T* data, const size_t& size) noexcept
{
	if (m_openMode != OpenMode::Write_Mode)
		return;

	m_fp.write(reinterpret_cast<char*>(data), size);
}

template<class T>
inline void FileStream::Write(std::vector<T> data) noexcept
{
	if (m_openMode != OpenMode::Write_Mode)
		return;

	size_t size = data.size();
	m_fp.write(reinterpret_cast<char*>(&size), sizeof(size_t));
	m_fp.write(reinterpret_cast<char*>(data.data()), sizeof(T) * data.size());
}

template<>
inline void FileStream::Write(std::vector<std::string> data) noexcept
{
	/** ファイルデータの先頭から一行ずつ書き込み */
	if (m_openMode == OpenMode::Txt_Mode)
	{
		m_fp.clear();
		for (const auto& addText : data)
		{
			m_fp << addText;
		}
	}
	else if (m_openMode == OpenMode::Write_Mode)
	{
		size_t size = data.size();
		m_fp.write(reinterpret_cast<char*>(&size), sizeof(size_t));

		for (const auto& buf : data)
		{
			m_fp.write(reinterpret_cast<char*>(buf.length()), sizeof(size_t));
			m_fp.write(const_cast<char*>(buf.data()), buf.length());
		}
	}
}

template<class T>
inline void FileStream::Read(T* data) noexcept
{
	if (m_openMode != OpenMode::Read_Mode)
		return;

	m_fp.read(reinterpret_cast<char*>(data), sizeof(T));
}

template<>
inline void FileStream::Read<std::string>(std::string* data) noexcept
{
	if (m_openMode != OpenMode::Read_Mode)
		return;

	size_t length = 0;
	m_fp.read(reinterpret_cast<char*>(&length), sizeof(size_t));

	data->resize(length);
	m_fp.read(reinterpret_cast<char*>(data->data()), length);
}

template<class T>
inline void FileStream::Read(T* data, const size_t& size) noexcept
{
	if (m_openMode != OpenMode::Read_Mode)
		return;

	m_fp.read(reinterpret_cast<char*>(data), size);
}

template<class T>
inline void FileStream::Read(std::vector<T>* data) noexcept
{
	if (m_openMode != OpenMode::Read_Mode)
		return;

	size_t size;
	m_fp.read(reinterpret_cast<char*>(&size), sizeof(size_t));

	data->resize(size);
	m_fp.read(reinterpret_cast<char*>(data->data()), sizeof(T) * data->size());
}

template<>
inline void FileStream::Read<std::string>(std::vector<std::string>* data) noexcept
{
	if (m_openMode == OpenMode::Txt_Mode)
	{
		m_fp.clear();
		m_fp.seekp(std::ios::beg);

		// 終端チェック
		while (!m_fp.eof())
		{
			std::string buf;
			std::getline(m_fp, buf);
			buf += "\n";
			data->push_back(std::move(buf));
		}
	}
	else if (m_openMode == OpenMode::Read_Mode) 
	{
		size_t size;
		m_fp.read(reinterpret_cast<char*>(&size), sizeof(size_t));

		data->resize(size);
		for (int i = 0; i < size; ++i)
		{
			size_t length = 0;
			m_fp.read(reinterpret_cast<char*>(&length), sizeof(size_t));

			data[i].resize(length);
			m_fp.read(reinterpret_cast<char*>(data[i].data()), length);
		}
	}
}
#endif // USE_C