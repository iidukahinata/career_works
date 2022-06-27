/**
* @file    RenderObject.h
* @brief
*
* @date	   2022/06/27 2022îNìxèâî≈
*/
#pragma once


#include "../IComponent.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"

class RenderObject : public IComponent
{
public:

	virtual void Initialize() override;
	virtual void Remove() override;

	virtual void Render() = 0;
};

class MeshRender : public RenderObject
{
public:

	void Initialize() override;

	void SetModel(std::string_view name) noexcept;
	void Render() override;

private:

	Model* m_model;
};