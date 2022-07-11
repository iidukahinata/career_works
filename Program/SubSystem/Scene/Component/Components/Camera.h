/**
* @file    Camera.h
* @brief
*
* @date	   2022/07/09 2022îNìxèâî≈
*/
#pragma once


#include "../IComponent.h"

class Renderer;

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

	const Math::Matrix& GetViewMatrix();
	const Math::Matrix& GetProjectionMatrix();
	const Math::Matrix& GetOrthographicMatrix();

private:

	void CreateProjectionMatrix();
	void CreateOrthographicMatrix();

private:

	Math::Matrix m_projection;
	Math::Matrix m_orthographic;

	float m_aspect;
	float m_width;
	float m_height;
	float m_fov;
	float m_near;
	float m_far;

	Renderer* m_renderer;
};