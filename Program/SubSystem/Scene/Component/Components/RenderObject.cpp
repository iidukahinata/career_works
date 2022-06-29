/**
* @file    RenderObject.cpp
* @brief
*
* @date	   2022/06/29 2022�N�x����
*/


#include "RenderObject.h"
#include "SubSystem/Core/Common/Common.h"
#include "SubSystem/Renderer/Renderer.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"

void RenderObject::Initialize()
{
	m_renderer = GetContext()->GetSubsystem<Renderer>();

	RegisterToRenderer();

	Do_Initialize();
}

void RenderObject::Remove()
{
	UnRegisterFromRenderer();

	Do_Remove();
}

void RenderObject::Active(bool active)
{
	if (IsActive() == active)
	{
		return;
	}

	IComponent::Active(active);
	if (active)
	{
		RegisterToRenderer();
	}
	else
	{
		UnRegisterFromRenderer();
	}
}

void RenderObject::RegisterToRenderer()
{
	ASSERT(m_renderer);
	m_renderer->RegisterRenderObject(this);
}

void RenderObject::UnRegisterFromRenderer()
{
	ASSERT(m_renderer);
	m_renderer->RemoveRenderObject(this);
}

void MeshRender::Do_Initialize()
{
	// �f�o�b�O�p���f��
	SetModel("Renault.model");
	GetTransform().SetScale(Math::Vector3(0.01f));
}

void MeshRender::SetModel(std::string_view name) noexcept
{
	m_model = GetContext()->GetSubsystem<ResourceManager>()->Load<Model>(name);
}

void MeshRender::Render()
{
	// �����[�u
	auto rot = GetTransform().GetRotation();
	rot.y += 0.01f;
	GetTransform().SetRotation(rot);

	TransformCBuffer::Get().Bind(GetTransform().GetWorldMatrix().ToMatrixXM());

	m_model->Render();
}