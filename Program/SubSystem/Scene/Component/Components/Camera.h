/**
* @file    Camera.h
* @brief
*
* @date	   2022/06/27 2022îNìxèâî≈
*/
#pragma once


#include "../IComponent.h"

class Camera : public IComponent
{
	SUB_CLASS(Camera)
public:

	void Initialize() override;
	void Remove() override;

	float GetWidth() const;
	void SetWidth(float width);
	float GetHeight() const;
	void SetHeight(float height);

	float GetAspect() const;
	void SetAspect(float aspect);

	float GetFov() const;
	void SetFov(float fov);
	float GetNear() const;
	void SetNear(float nearClip);
	float GetFar() const;
	void SetFar(float farClip);

	DirectX::XMMATRIX GetViewMatrixXM();
	DirectX::XMMATRIX GetProjectionMatrixXM();
	DirectX::XMMATRIX GetOrthographicMatrixXM();

private:

	void CreateProjectionMatrix();
	void CreateOrthographicMatrix();

private:

	DirectX::XMMATRIX m_projection;
	DirectX::XMMATRIX m_orthographic;

	float m_aspect;
	float m_width;
	float m_height;
	float m_fov;
	float m_near;
	float m_far;
};