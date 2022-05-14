/**
* @file    Matrix.cpp
* @brief
*
* @date	   2021/07/01 2021îNìxèâî≈
* @author  î—íÀózëæ
*/


#include "Matrix.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Math 
{
	const Matrix Matrix::Identity(1, 0, 0, 0,
								  0, 1, 0, 0,
								  0, 0, 1, 0,
								  0, 0, 0, 1);

	constexpr Matrix::Matrix(const Vector4& InX, const Vector4& InY, const Vector4& InZ, const Vector4& InW) noexcept
	{
		m[0][0] = InX.x; m[0][1] = InX.y;  m[0][2] = InX.z;  m[0][3] = InX.w;
		m[1][0] = InY.x; m[1][1] = InY.y;  m[1][2] = InY.z;  m[1][3] = InY.w;
		m[2][0] = InZ.x; m[2][1] = InZ.y;  m[2][2] = InZ.z;  m[2][3] = InZ.w;
		m[3][0] = InW.x; m[3][1] = InW.y;  m[3][2] = InW.z;  m[3][3] = InW.w;
	}

	Matrix::Matrix(const Vector3& position, const Vector3& eulerAngles, const Vector3& scale) noexcept
	{
		auto world = DirectX::XMMatrixScalingFromVector(DirectX::XMLoadFloat3(&scale)) *
			DirectX::XMMatrixRotationX(eulerAngles.x) *
			DirectX::XMMatrixRotationY(eulerAngles.y) *
			DirectX::XMMatrixRotationZ(eulerAngles.z) *
			DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&position));

		DirectX::XMStoreFloat4x4(this, world);
	}

	Matrix Matrix::CreateTranslation(const Vector3& position) noexcept
	{
		Matrix translation;
		DirectX::XMStoreFloat4x4(&translation, DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&position)));
		return translation;
	}

	Matrix Matrix::CreateRotation(const Vector3& eulerAngles) noexcept
	{
		Matrix rotation;
		DirectX::XMStoreFloat4x4(
			&rotation,
			DirectX::XMMatrixRotationX(eulerAngles.x) *
			DirectX::XMMatrixRotationY(eulerAngles.y) *
			DirectX::XMMatrixRotationZ(eulerAngles.z));
		return rotation;
	}

	Matrix Matrix::CreateScaling(const Vector3& scale) noexcept
	{
		Matrix scaling;
		DirectX::XMStoreFloat4x4(&scaling, DirectX::XMMatrixScalingFromVector(DirectX::XMLoadFloat3(&scale)));
		return scaling;
	}

	Vector3 Matrix::TransformPosition(const Vector3& position) const noexcept
	{
		Vector3 result;
		DirectX::XMStoreFloat3(&result, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&position), ToMatrixXM()));
		return result;
	}

	Vector3 Matrix::GetTranslation() const noexcept
	{
		return Vector3(m[3][0], m[3][1], m[3][2]);
	}

	Vector3 Matrix::GetEulerAngles() const noexcept
	{
		float c = sqrtf(1.0f - m[2][1] * m[2][1]);
		if (isnan(c))
			c = 0.0f;

		return Vector3(atan2f(-m[2][1], std::move(c)), atan2f(m[2][0], m[2][2]), atan2f(m[0][1], m[1][1]));
	}
}