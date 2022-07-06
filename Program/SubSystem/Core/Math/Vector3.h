/**
* @file    Vector3.h
* @brief
*
* @date	   2022/06/01 2022�N�x����
*/
#pragma once


#include"MathHelper.h"
#include"Vector2.h"

namespace Math
{
	struct Vector3 : public DirectX::XMFLOAT3
	{
	public:

		// * vector (0.0f, 0.0f, 0.0f)
		static const Vector3 Zero;

		// * vector ( 1.0f, 1.0f, 1.0f)
		static const Vector3 One;

		// * vector ( 0.0f, 0.0f, 1.0f)
		static const Vector3 Up;

		// * vector ( 0.0f, 0.0f,-1.0f)
		static const Vector3 Down;

		// * vector ( 1.0f, 0.0f, 0.0f)
		static const Vector3 Forward;

		// * vector (-1.0f, 0.0f, 0.0f)
		static const Vector3 BackForward;

		// * vector ( 0.0f, 1.0f, 0.0f)
		static const Vector3 Right;

		// * vector ( 0.0f,-1.0f, 0.0f)
		static const Vector3 Left;

	public:

		constexpr Vector3() noexcept : DirectX::XMFLOAT3(0, 0, 0)
		{}

		explicit constexpr Vector3(float value) noexcept : DirectX::XMFLOAT3(value, value, value)
		{}

		explicit Vector3(const Vector4& V) noexcept;

		constexpr Vector3(const Vector3& V) noexcept : DirectX::XMFLOAT3(V.x, V.y, V.z)
		{}

		explicit constexpr Vector3(const Vector2& V, float z) noexcept : DirectX::XMFLOAT3(V.x, V.y, z)
		{}

		constexpr Vector3(float x, float y, float z) noexcept : DirectX::XMFLOAT3(x, y, z)
		{}

		const float& operator[](int index) const
		{
			ASSERT(0 <= index);
			ASSERT(index < 3);
			return (&x)[index];
		}

		float& operator[](int index)
		{
			ASSERT(0 <= index);
			ASSERT(index < 3);
			return (&x)[index];
		}

		constexpr Vector3 operator-() const noexcept
		{
			return Vector3(-x, -y, -z);
		}

		constexpr Vector3 operator+(const Vector3& V) const noexcept
		{
			return Vector3(x + V.x, y + V.y, z + V.z);
		}

		constexpr Vector3 operator+(float value) const noexcept
		{
			return Vector3(x + value, y + value, z + value);
		}

		constexpr Vector3 operator-(const Vector3& V) const noexcept
		{
			return Vector3(x - V.x, y - V.y, z - V.z);
		}

		constexpr Vector3 operator-(float value) const noexcept
		{
			return Vector3(x - value, y - value, z - value);
		}

		constexpr Vector3 operator*(const Vector3& V) const noexcept
		{
			return Vector3(x * V.x, y * V.y, z * V.z);
		}

		constexpr Vector3 operator*(float value) const noexcept
		{
			return Vector3(x * value, y * value, z * value);
		}

		constexpr Vector3 operator/(const Vector3& V) const
		{
			return Vector3(x / V.x, y / V.y, z / V.z);
		}

		constexpr Vector3 operator/(float value) const
		{
			return Vector3(x / value, y / value, z / value);
		}

		constexpr Vector3 operator+=(const Vector3& V) noexcept
		{
			x += V.x;
			y += V.y;
			z += V.z;
			return *this;
		}

		constexpr Vector3 operator+=(float value) noexcept
		{
			x += value;
			y += value;
			z += value;
			return *this;
		}

		constexpr Vector3 operator-=(const Vector3& V) noexcept
		{
			x -= V.x;
			y -= V.y;
			z -= V.z;
			return *this;
		}

		constexpr Vector3 operator-=(float value) noexcept
		{
			x -= value;
			y -= value;
			z -= value;
			return *this;
		}

		constexpr Vector3 operator*=(const Vector3& V) noexcept
		{
			x *= V.x;
			y *= V.y;
			z *= V.z;
			return *this;
		}

		constexpr Vector3 operator*=(float value) noexcept
		{
			x *= value;
			y *= value;
			z *= value;
			return *this;
		}

		constexpr Vector3 operator/=(const Vector3& V)
		{
			x /= V.x;
			y /= V.y;
			z /= V.z;
			return *this;
		}

		constexpr Vector3 operator/=(float value)
		{
			x /= value;
			y /= value;
			z /= value;
			return *this;
		}

		Vector3 Cross(const Vector3& V) const noexcept
		{
			return Cross(*this, V);
		}

		static Vector3 Cross(const Vector3& A, const Vector3& B) noexcept
		{
			Vector3 result;
			auto v = DirectX::XMVector3Cross(DirectX::XMLoadFloat3(&A), DirectX::XMLoadFloat3(&B));
			DirectX::XMStoreFloat3(&result, std::move(v));
			return result;
		}

		float Dot(const Vector3& V) const noexcept
		{
			return Dot(*this, V);
		}

		static float Dot(const Vector3& A, const Vector3& B) noexcept
		{
			float result;
			auto v = DirectX::XMVector3Dot(DirectX::XMLoadFloat3(&A), DirectX::XMLoadFloat3(&B));
			DirectX::XMStoreFloat(&result, std::move(v));
			return result;
		}

		void Normalize() noexcept
		{
			DirectX::XMStoreFloat3(this, DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(this)));
		}

		float GetLenght() const noexcept
		{
			float result;
			DirectX::XMStoreFloat(&result, DirectX::XMVector3Length(DirectX::XMLoadFloat3(this)));
			return result;
		}

		float GetSquaredLength() const noexcept
		{
			return x * x + y * y + z * z;
		}

		float Distance(const Vector3& V) const noexcept
		{
			return Distance(*this, V);
		}

		static float Distance(const Vector3& A, const Vector3& B) noexcept
		{
			return (B - A).GetLenght();
		}

		float DistanceSquared(const Vector3& V) const noexcept
		{
			return DistanceSquared(*this, V);
		}

		static float DistanceSquared(const Vector3& A, const Vector3& B) noexcept
		{
			return (B - A).GetSquaredLength();
		}

		bool operator==(const Vector3& V) const noexcept
		{
			return x == V.x && y == V.y && z == V.z;
		}

		bool operator!=(const Vector3& V) const noexcept
		{
			return x != V.x || y != V.y || z != V.z;
		}

		bool Equals(const Vector3& V, float tolerance = MINUTE_VALUE) const noexcept
		{
			return Equals(*this, V, tolerance);
		}

		static bool Equals(const Vector3& A, const Vector3& B, float tolerance = MINUTE_VALUE) noexcept
		{
			auto dis = A - B;
			return fabs(dis.x) <= tolerance && fabs(dis.y) <= tolerance && fabs(dis.z) <= tolerance;
		}

		String ToString() const noexcept
		{
			char buffer[128];
			// ���g�̃f�[�^�𕶎���ɕϊ�����
			sprintf_s(buffer, "X:%f, Y:%f, Z:%f", x, y, z);
			return buffer;
		}
	};
}