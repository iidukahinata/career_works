/**
* @file    MeshRender.cpp
* @brief
*
* @date	   2022/06/30 2022�N�x����
*/


#include "RenderObject.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"

void MeshRender::Do_Initialize()
{
	// �f�o�b�O�p���f��
	SetModel("Renault.model");
	GetTransform().SetScale(Math::Vector3(0.01f));
}

void MeshRender::SetModel(StringView name) noexcept
{
	m_model = GetContext()->GetSubsystem<ResourceManager>()->Load<Model>(name);
}

void MeshRender::Render() const
{
	TransformCBuffer::Get().Bind(GetTransform().GetWorldMatrix().ToMatrixXM());

	m_model->Render();
}