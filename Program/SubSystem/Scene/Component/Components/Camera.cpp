/**
* @file    Camera.cpp
* @brief
*
* @date	   2022/06/29 2022年度初版
*/


#include "Camera.h"
#include "SubSystem/Renderer/TransformCBuffer.h"
#include "SubSystem/Window/Window.h"

void Camera::Initialize()
{
	m_fov = DirectX::XMConvertToRadians(45.0f);
	m_width = Window::Get().GetWindowWidth();
	m_height = Window::Get().GetWindowHeight();
	m_aspect = m_width / m_height;
	m_near = 0.1f;
	m_far = 1000.0f;

	// create matrix
	CreateProjectionMatrix();
	CreateOrthographicMatrix();

	GetTransform().SetPosition(Math::Vector3(0.f, 3.f, -8.f));
	GetTransform().LockAt(Math::Vector3::Zero);

	// 更新処理がないためここに初期化時に書いている。
	TransformCBuffer::Get().SetProjection(GetProjectionMatrixXM());
	TransformCBuffer::Get().SetView(GetViewMatrix().ToMatrixXM());
}

void Camera::Remove()
{

}

float Camera::GetAspect() const
{
	return m_aspect;
}

void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
	CreateProjectionMatrix();
}

float Camera::GetWidth() const
{
	return m_width;
}

void Camera::SetWidth(float width)
{
	m_width = width;
	CreateOrthographicMatrix();
}

float Camera::GetHeight() const
{
	return m_height;
}

void Camera::SetHeight(float height)
{
	m_height = height;
	CreateOrthographicMatrix();
}

float Camera::GetFov() const
{
	return m_fov;
}

void Camera::SetFov(float fov)
{
	m_fov = fov;
	CreateProjectionMatrix();
}

float Camera::GetNear() const
{
	return m_near;
}

void Camera::SetNear(float nearClip)
{
	m_near = nearClip;
	CreateProjectionMatrix();
	CreateOrthographicMatrix();
}

float Camera::GetFar() const
{
	return m_far;
}

void Camera::SetFar(float farClip)
{
	m_far = farClip;
	CreateProjectionMatrix();
	CreateOrthographicMatrix();
}

Math::Matrix Camera::GetViewMatrix()
{
	return GetTransform().GetWorldMatrix().Inverse();
}

DirectX::XMMATRIX Camera::GetProjectionMatrixXM()
{
	return m_projection;
}

DirectX::XMMATRIX Camera::GetOrthographicMatrixXM()
{
	return m_orthographic;
}

void Camera::CreateProjectionMatrix()
{
	m_projection = DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_near, m_far);
}

void Camera::CreateOrthographicMatrix()
{
	m_orthographic = DirectX::XMMatrixOrthographicLH(m_width, m_height, m_near, m_far);
}