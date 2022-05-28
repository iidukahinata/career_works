#pragma once


#include "SubSystem/Math/Vector3.h"
#include "SubSystem/Math/Vector4.h"
#include "LinearMath/btQuaternion.h"

inline Math::Vector3 ToVector3(const btVector3& V)
{
	return Math::Vector3(V.getX(), V.getY(), V.getZ());
}

inline btVector3 ToBtVector3(const Math::Vector3& V)
{
	return btVector3(V.x, V.y, V.z);
}

inline btQuaternion ToBtQuaternion(const Math::Vector4& V)
{
	return btQuaternion(V.x, V.y, V.z, V.w);
}

inline Math::Vector4 ToVector4(const btQuaternion& Q)
{
	return Math::Vector4(Q.getX(), Q.getY(), Q.getZ(), Q.getZ());
}