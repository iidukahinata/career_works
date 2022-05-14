#pragma once


#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"

class Player : public IGameObject
{
public:

	// IGameObject
	void Init() override;
	void Update() override;
	void Draw() override;

private:

	Model m_model;
};