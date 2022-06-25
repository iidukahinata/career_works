/**
* @file    Transform.h
* @brief
*
* @date	   2022/06/25 2022年度初版
*/
#pragma once


#include "../IComponent.h"
#include "SubSystem/Core/Math/Matrix.h"
#include "SubSystem/Core/Math/Vector3.h"

/**
* 変換系はDirectXMathを使用して計算を行っている
*/
class Transform : public IComponent
{
	SUB_CLASS(Transform)
public:

	Transform();

	void SetPosition(const Math::Vector3& position) noexcept;
	const Math::Vector3& GetPosition() const noexcept;
	const Math::Vector3& GetWoldPosition() const;

	void SetRotation(const Math::Vector3& rotation) noexcept;
	const Math::Vector3& GetRotation() const noexcept;

	void SetScale(const Math::Vector3& scale) noexcept;
	const Math::Vector3& GetScale() const noexcept;

	Math::Matrix GetLocalMatrix() const;
	DirectX::XMMATRIX GetLocalMatrixXM() const;
	Math::Matrix GetWorldMatrix() const;
	DirectX::XMMATRIX GetWorldMatrixXM() const;

	const Math::Vector3& GetRight() const noexcept;
	const Math::Vector3& GetUp() const noexcept;
	const Math::Vector3& GetForward() const noexcept;

	void LockAt(const Math::Vector3& target, const Math::Vector3& up = Math::Vector3::Right);
	void LockTo(const Math::Vector3& direction, const Math::Vector3& up = Math::Vector3::Right);

	void SetPearent(Transform* parent) noexcept;
	Transform* GetPearent() const noexcept;
	Transform* GetRoot() const noexcept;

private:

	Transform* m_parent = nullptr;

	Math::Vector3 m_localPosition;
	Math::Vector3 m_localRotation;
	Math::Vector3 m_localScale;

	Math::Vector3 m_up;
	Math::Vector3 m_forward;
	Math::Vector3 m_right;
};