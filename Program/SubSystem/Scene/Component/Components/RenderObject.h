/**
* @file    RenderObject.h
* @brief
*
* @date	   2022/06/29 2022�N�x����
*/
#pragma once


#include "../IComponent.h"

class Model;
class Renderer;

class RenderObject : public IComponent
{
	SUB_CLASS(RenderObject)

	friend class Renderer;
public:

	void Initialize() override;
	void Remove() override;

	virtual void Active(bool active) override;

protected:

	virtual void Do_Initialize() {}
	virtual void Do_Remove() {}

	/** �e�`�揈�����L�q�B*/
	virtual void Render() = 0;

	void RegisterToRenderer();
	void UnRegisterFromRenderer();

private:

	Renderer* m_renderer;
};

class MeshRender : public RenderObject
{
	SUB_CLASS(MeshRender)
public:

	void SetModel(std::string_view name) noexcept;

private:

	void Do_Initialize() override;
	void Render() override;

private:

	Model* m_model;
};