/**
* @file    RenderObject.cpp
* @brief
*
* @date	   2022/06/26 2022年度初版
*/


#include "RenderObject.h"
#include "SubSystem/Renderer/Renderer.h"
#include "SubSystem/Resource/ResourceManager.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Resource/Resources/3DModel/Model.h"

void RenderObject::Initialize()
{
	GetContext()->GetSubsystem<Renderer>()->RegisterRenderObject(this);
}

void RenderObject::Remove()
{
	GetContext()->GetSubsystem<Renderer>()->RemoveRenderObject(this);
}

void MeshRender::Initialize()
{
	RenderObject::Initialize();

	// デバッグ用仮素材
	SetModel("Renault.model");
	GetTransform().SetScale(Math::Vector3(0.01f));
}

void MeshRender::SetModel(std::string_view name) noexcept
{
	m_model = GetContext()->GetSubsystem<ResourceManager>()->Load<Model>(name);
}

void MeshRender::Render()
{
	// 仮ムーブ
	auto rot = GetTransform().GetRotation();
	rot.y += 0.01f;
	GetTransform().SetRotation(rot);

	TransformCBuffer::Get().Bind(GetTransform().GetWorldMatrix().ToMatrixXM());

	m_model->Render();
}