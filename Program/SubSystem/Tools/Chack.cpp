/**
* @file    Chack.cpp
* @brief
*
* @date	   2022/05/28 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
* @note
*/


#include "Chack.h"
#include <string>
#include "SubSystem/Log/DebugLog.h"

#ifdef _DEBUG
void chack(const char* message, const char* file, unsigned line, const char* text)
{
	std::string buf;
	buf += std::string(text);
	buf += std::string("\n\nprogram: ") + file;
	buf += std::string("\n\nline: ") + std::to_string(line);
	buf += std::string("\n\nexpr: ") + message;
	LOG_ERROR(buf);
}
#endif // _DEBUG