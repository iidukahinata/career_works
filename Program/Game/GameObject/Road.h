#pragma once


#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Resource/Resources/3DModel/Quad.h"

class Road : public IGameObject
{
public:

	void Init() override;
	void Update() override;
	void Draw() override;

private:

	Quad m_quad;
};