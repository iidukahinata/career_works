/**
* @file		Camera.h
* @brief	カメラ基底クラス
*
* @date	   2022/04/22 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "SubSystem/Scene/Transform.h"

class Camera
{
public:

	Camera();

	virtual void Update(Math::Vector3 playerPos, Math::Vector3 forwardVec) {}

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

	Transform& GetTransform();

	DirectX::XMMATRIX GetViewMatrixXM();
	DirectX::XMMATRIX GetProjectionMatrixXM();
	DirectX::XMMATRIX GetOrthographicMatrixXM();

private:

	void CreateProjectionMatrix();
	void CreateOrthographicMatrix();

protected:

	DirectX::XMMATRIX m_projection;
	DirectX::XMMATRIX m_orthographic;

	float m_aspect;
	float m_width;
	float m_height;
	float m_fov;
	float m_near;
	float m_far;

	Transform m_transform;
};