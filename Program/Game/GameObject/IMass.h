#pragma once


#include "SubSystem/Scene/GameObject.h"

class IMass : public IGameObject
{
public:

	// IGameObject
	virtual void Awake() override {}
	virtual void Init() override {}
	virtual void Update() override {}
	virtual void Draw() override {}

	virtual const char* GetName() override;

protected:

	Math::Vector3 m_massSize = Math::Vector3(0.01f);
};