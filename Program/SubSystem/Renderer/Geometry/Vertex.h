/**
* @file	   Vertex.h
* @brief
*
* @date	   2022/07/01 2022îNìxèâî≈
*/
#pragma once


#include "SubSystem/Core/Math/MathCore.h"

struct Vertex2D
{
	Math::Vector3 position;
	Math::Vector2 tex;
};

struct Vertex3D
{
	Math::Vector3 position;
	Math::Vector2 tex;
	Math::Vector3 normal;
};

struct VertexBump3D
{
	Math::Vector3 position;
	Math::Vector2 tex;
	Math::Vector3 normal;
	Math::Vector3 tangent;
	Math::Vector3 biNormal;
};