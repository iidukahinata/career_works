/**
* @file    Transform.cpp
* @brief
*
* @date	   2022/05/10 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/


#include "Transform.h"
#include "GameObject.h"

Transform::Transform() :
	m_localPosition(0.f, 0.f, 0.f),
	m_localRotation(0.f, 0.f, 0.f),
	m_localScale(1.f, 1.f, 1.f)
{}

Transform::Transform(IGameObject* object) :
	m_object(object),
	m_localPosition(0.f, 0.f, 0.f),
	m_localRotation(0.f, 0.f, 0.f),
	m_localScale(1.f, 1.f, 1.f)
{}

void Transform::SetPosition(const Math::Vector3& position) noexcept
{
	m_localPosition = position;
}

const Math::Vector3& Transform::GetPosition() const noexcept
{
	return m_localPosition;
}

const Math::Vector3& Transform::GetWoldPosition() const
{
	return GetWorldMatrix().TransformPosition(m_localPosition);
}

void Transform::SetRotation(const Math::Vector3& rotation) noexcept
{
	m_localRotation = rotation;
}

const Math::Vector3& Transform::GetRotation() const noexcept
{
	return m_localRotation;
}

void Transform::SetScale(const Math::Vector3& scale) noexcept
{
	m_localScale = scale;
}

const Math::Vector3& Transform::GetScale() const noexcept
{
	return m_localScale;
}

void Transform::LockAt(const Math::Vector3& target, const Math::Vector3& up /* = Math::Vector3::Right */)
{
	auto view = DirectX::XMMatrixLookAtLH(
		DirectX::XMLoadFloat3(&m_localPosition),
		DirectX::XMLoadFloat3(&target),
		DirectX::XMLoadFloat3(&up));

	DirectX::XMMATRIX invView = DirectX::XMMatrixInverse(nullptr, std::move(view));
	Math::Matrix rotMatrix;
	DirectX::XMStoreFloat4x4(&rotMatrix, std::move(invView));
	m_localRotation = rotMatrix.GetEulerAngles();
}

void Transform::LockTo(const Math::Vector3& direction, const Math::Vector3& up /* = Math::Vector3::Right */)
{
	auto view = DirectX::XMMatrixLookToLH(
		DirectX::XMLoadFloat3(&m_localPosition),
		DirectX::XMLoadFloat3(&direction),
		DirectX::XMLoadFloat3(&up));

	DirectX::XMMATRIX invView = DirectX::XMMatrixInverse(nullptr, std::move(view));
	Math::Matrix rotMatrix;
	DirectX::XMStoreFloat4x4(&rotMatrix, std::move(invView));
	m_localRotation = rotMatrix.GetEulerAngles();
}

Math::Matrix Transform::GetLocalMatrix() const
{
	return Math::Matrix(m_localPosition, m_localRotation, m_localScale);
}

DirectX::XMMATRIX Transform::GetLocalMatrixXM() const
{
	return GetLocalMatrix().ToMatrixXM();
}

Math::Matrix Transform::GetWorldMatrix() const
{
	auto result = GetLocalMatrix();
	auto parent = m_parent;
	while (parent)
	{
		result *= m_parent->GetLocalMatrix();
		parent = parent->m_parent;
	}
	return result;
}

DirectX::XMMATRIX Transform::GetWorldMatrixXM() const
{
	return GetWorldMatrix().ToMatrixXM();
}

Math::Vector3 Transform::GetUp()
{
	auto rot = Math::Matrix::CreateRotation(m_localRotation);
	return Math::Vector3(rot.m[1][0], rot.m[1][1], rot.m[1][2]);
}

Math::Vector3 Transform::GetForward()
{
	auto rot = Math::Matrix::CreateRotation(m_localRotation);
	return Math::Vector3(rot.m[2][0], rot.m[2][1], rot.m[2][2]);
}

void Transform::SetPearent(IGameObject* parent) noexcept
{
	if (parent)
	{
		m_parent = &parent->GetTransform();
	}
	else
	{
		m_parent = nullptr;
	}
}

IGameObject* Transform::GetPearent() const noexcept
{
	if (m_parent)
	{
		return m_parent->m_object;
	}
	else
	{
		return nullptr;
	}
}