/**
* @file    AudioListener.h
* @brief
*
* @date	   2022/06/27 2022年度初版
*/
#pragma once


#include <fmod.hpp>
#include "../IComponent.h"

/**
* 3D サウンドを使用する場合は必ず使用する必要があります。
*/
class AudioListener : public IComponent
{
	SUB_CLASS(AudioListener)
public:

	~AudioListener();

	FMOD_VECTOR GetPosition() const noexcept;
	FMOD_VECTOR GetForward() const noexcept;
	FMOD_VECTOR GetUp() const noexcept;

	void SetVelocity(const Math::Vector3& velocity) noexcept;
	FMOD_VECTOR GetVelocity() const noexcept;

private:

	Math::Vector3 m_velocity;
};