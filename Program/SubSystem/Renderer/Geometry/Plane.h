/**
* @file	   Plane.h
* @brief	板ポリ生成クラス
*
* @date	   2022/04/27 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "SubSystem/Resource/Resources/3DModel/Mesh.h"

class Plane
{
public:

	template<class T>
	static Mesh<T> Make(float width = 1.f, float height = 1.f) 
	{
		const Math::Vector2 halfSize(width / 2.f, height / 2.f);

		std::vector<T> vertices(4);

		vertices[0].position = Math::Vector3( halfSize.x,  halfSize.y, 0.f);
		vertices[1].position = Math::Vector3(-halfSize.x,  halfSize.y, 0.f);
		vertices[2].position = Math::Vector3(-halfSize.x, -halfSize.y, 0.f);
		vertices[3].position = Math::Vector3( halfSize.x, -halfSize.y, 0.f);

		vertices[0].tex = Math::Vector2(1, 0);
		vertices[1].tex = Math::Vector2(0, 0);
		vertices[2].tex = Math::Vector2(0, 1);
		vertices[3].tex = Math::Vector2(1, 1);

		std::vector<UINT> indices = { 0, 1, 2, 2, 3, 0 };

		std::vector<Texture*> textures;
		return Mesh<T>(std::move(vertices), std::move(textures), std::move(indices));
	}
};