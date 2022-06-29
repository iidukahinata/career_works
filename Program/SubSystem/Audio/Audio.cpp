/**
* @file    Audio.cpp
* @brief
*
* @date	   2022/06/28 2022�N�x����
*/


#include "Audio.h"
#include "Subsystem/Scene/Component/Components/AudioListener.h"

void Audio::SetAudioListener(AudioListener* const listener) noexcept
{
	m_lisrener = listener;
}