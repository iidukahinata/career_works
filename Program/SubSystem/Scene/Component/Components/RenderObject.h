/**
* @file    RenderObject.h
* @brief
*
* @date	   2022/06/27 2022îNìxèâî≈
*/
#pragma once


#include "../IComponent.h"

class Model;

class RenderObject : public IComponent
{
	SUB_CLASS(RenderObject)
public:

	virtual void Initialize() override;
	virtual void Remove() override;

	virtual void Render() = 0;
};

class MeshRender : public RenderObject
{
	SUB_CLASS(MeshRender)
public:

	void Initialize() override;

	void SetModel(std::string_view name) noexcept;
	void Render() override;

private:

	Model* m_model;
};