/**
* @file	   Vertex.h
* @brief
*
* @date	   2022/07/06 2022?N?x????
*/
#pragma once


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