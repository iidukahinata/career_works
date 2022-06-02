/**
* @file    IMass.h
* @brief
*
* @date	   2022/06/02 2022îNìxèâî≈
* @author  î—íÀózëæ
*/
#pragma once


#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Math/Vector3T.h"

class IMass : public IGameObject
{
public:

	enum class MassType
	{
		PLAYER,
		ENEMY,
		ITEM,
		MESSEGE
	};

	// IGameObject
	virtual void Awake() override {}
	virtual void Init() override {}
	virtual void Update() override {}
	virtual void Draw() override {}

	virtual const char* GetName() override;
	virtual MassType GetType() = 0;

	void SetMassPos(Math::Vector3i pos) noexcept;

protected:

	Math::Vector3 m_massSize = Math::Vector3(0.01f);

	Math::Vector3i m_massPos;
};