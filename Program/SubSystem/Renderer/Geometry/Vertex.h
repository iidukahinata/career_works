/**
* @file	   Vertex.h
* @brief
*
* @date	   2022/05/06 2022”N“x‰”Å
* @author  ”Ñ’Ë—z‘¾
*/
#pragma once


#include "SubSystem/Math/MathCore.h"

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