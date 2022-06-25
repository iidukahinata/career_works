/**
* @file    COM.cpp
* @brief
*
* @date	   2022/05/14 2022�N�x����
* @author  �ђ˗z��
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