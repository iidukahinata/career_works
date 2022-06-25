/**
* @file    COM.cpp
* @brief
*
* @date	   2022/06/25 2022îNìxèâî≈
*/


#include <objbase.h>
#include "COM.h"

COM::COM()
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
}

COM::COM(COMID comID)
{
	HRESULT hr = CoInitializeEx(NULL, static_cast<DWORD>(comID));
}

COM::~COM()
{
	CoUninitialize();
}