///**
//* @file	   Cube.h
//* @brief   ボックス生成クラス
//*
//* @date	   2022/04/27 2022年度初版
//* @author  飯塚陽太
//*/
//#pragma once
//
//
//#include "SubSystem/Resource/Resources/3DModel/Mesh.h"
//
//class Cube
//{
//public:
//
//	template<class T>
//	static Mesh<T> Make() {
//
//		constexpr float size = 0.5f;
//		std::vector<T> vertices(8);
//
//		vertices[0].position = Math::Vector3(-size,  size, -size);
//		vertices[1].position = Math::Vector3( size,  size, -size);
//		vertices[2].position = Math::Vector3( size, -size, -size);
//		vertices[3].position = Math::Vector3(-size, -size, -size);
//		vertices[4].position = Math::Vector3(-size,  size,  size);
//		vertices[5].position = Math::Vector3( size,  size,  size);
//		vertices[6].position = Math::Vector3( size, -size,  size);
//		vertices[7].position = Math::Vector3(-size, -size,  size);
//
//		std::vector<UINT> indices = {
//			0, 1, 2,  2, 3, 0,// 前
//			5, 4, 7,  7, 6, 5,// 奥
//			4, 0, 7,  0, 3, 7,// 左
//			1, 5, 6,  1, 6, 2,// 右
//			0, 4, 1,  4, 5, 1,// 上
//			3, 2, 7,  6, 7, 2 // 下
//		};
//
//		std::vector<Texture*> textures;
//		return Mesh<T>(std::move(vertices), std::move(textures), std::move(indices));
//	}
//};