/**
* @file		AudioHelper.h
* @brief
*
* @date		2022/07/06 2022�N�x����
*/
#pragma once


#include <fmod_errors.h>

#define AUDIO_EORROR_CHECK(data)								\
if (data != FMOD_OK)											\
{																\
	LOG_ERROR(String("FMOD ERROR : ") + FMOD_ErrorString(data));\
}