/**
* @file    MathHelper.h
* @brief
*
* @date	   2021/07/01 2021”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/
#pragma once


#include <string>
#include <DirectXMath.h>
#include "SubSystem/Tools/Chack.h"

#define PI 3.14159265359f
#define PI_2 6.28318530718f
#define PI_4 12.5663706144f
#define VERY_SMALL_VALUE 1.0e-8f
#define MINUTE_VALUE 1.0e-4f

namespace Math
{
	struct Vector2;
	struct Vector3;
	struct Vector4;
	struct Matrix;

	constexpr float ToRadian(float degree)
	{
		constexpr float rad = PI / 180.f;
		return degree * rad;
	}

	constexpr float ToDegree(float radian)
	{
		constexpr float degree = 180.f / PI;
		return radian * degree;
	}
}