/**
* @file    AudioListener.h
* @brief
*
* @date	   2022/06/29 2022îNìxèâî≈
*/
#pragma once


#include "../IComponent.h"

class Audio;

class AudioListener : public IComponent
{
	SUB_CLASS(AudioListener)
public:

	void Initialize() override;
	void Remove() override;

	void Active(bool active) override;

	void SetVelocity(const Math::Vector3& velocity) noexcept;
	const Math::Vector3& GetVelocity() const noexcept;

private:

	void RegisterToAudioSystem();
	void UnRegisterFromAudioSystem();

private:

	Math::Vector3 m_velocity;

	Audio* m_audio;
};