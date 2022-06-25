/**
* @file    AudioListener.h
* @brief
*
* @date	   2022/05/10 2022�N�x����
* @author  �ђ˗z��
*/
#pragma once


#include <fmod.hpp>
#include "SubSystem/Core/Math/Vector3.h"
#include "../IComponent.h"
//#include "../Transform.h"

/**
* 3D �T�E���h���g�p����ꍇ�͕K���g�p����K�v������܂��B
*/
class AudioListener
{
public:

	~AudioListener();

	//void Init(Transform* parent) noexcept;

	//FMOD_VECTOR GetPosition() const noexcept;
	//FMOD_VECTOR GetForward() const noexcept;
	//FMOD_VECTOR GetUp() const noexcept;

	void SetVelocity(const Math::Vector3& velocity) noexcept;
	FMOD_VECTOR GetVelocity() const noexcept;

private:

	//Transform* m_parent = nullptr;

	Math::Vector3 m_velocity;
};