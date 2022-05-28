/**
* @file		Camera.cpp
* @brief	�J�������N���X
*
* @date	   2022/04/22 2022�N�x����
* @author  �ђ˗z��
*/


#include "Camera.h"
#include "SubSystem/Window/Window.h"

Camera::Camera()
{
	m_transform.SetPosition(Math::Vector3(0.f, 3.f, -10.f));

	m_fov = DirectX::XMConvertToRadians(45.0f);
	m_width = Window::Get().GetWindowWidth();
	m_height = Window::Get().GetWindowHeight();
	m_aspect = m_width / m_height;
	m_near = 0.1f;
	m_far = 1000.0f;

	// create matrix
	CreateProjectionMatrix();
	CreateOrthographicMatrix();
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

Transform& Camera::GetTransform()
{
	return m_transform;
}

DirectX::XMMATRIX Camera::GetViewMatrixXM()
{
	return DirectX::XMMatrixInverse(nullptr, m_transform.GetWorldMatrixXM());
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