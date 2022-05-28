#include "Chack.h"
#include "SubSystem/Log/DebugLog.h"
#include "SubSystem/Tools/Tools.h"

#ifdef _DEBUG
void chack(const char* text, const wchar_t* file, unsigned line)
{
	std::string buf(text);
	buf += std::string("\n\nprogram:") + ToString(file + std::wstring(L"  line:") + std::to_wstring(line));
	LOG_ERROR(buf);
}
#endif // _DEBUG