/**
* @file    RenderObject.h
* @brief
*
* @date	   2022/06/26 2022îNìxèâî≈
*/
#pragma once


#include "../IComponent.h"
#include "SubSystem/Resource/Resources/3DModel/Mesh.h"
#include "SubSystem/Resource/Resources/3DModel/Material.h"

class RenderObject : public IComponent
{
public:

	void Initialize() override;
	void Remove() override;
};

class MeshRender : public RenderObject
{
public:

private:
};