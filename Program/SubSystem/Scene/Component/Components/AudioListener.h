/**
* @file    AudioListener.h
* @brief
*
* @date	   2022/05/10 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include <fmod.hpp>
#include "SubSystem/Core/Math/Vector3.h"
#include "../IComponent.h"
//#include "../Transform.h"

/**
* 3D サウンドを使用する場合は必ず使用する必要があります。
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