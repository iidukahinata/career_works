/**
* @file    Material.h
* @brief
*
* @date	   2022/04/25 2022年度初版
* @author  飯塚陽太
*/
#pragma once


#include "SubSystem/Math/MathCore.h"

/**
* 2022/04/25 時点では使用されていないが、今後独自マテリアルデータとして使用予定。
* またその時はマテリアルでテクスチャデータを使用する予定。
*/
struct Material
{
	float m_alpha;
	Math::Vector3 m_ambient;	//環境色
	Math::Vector3 m_diffuse;	//ディフューズ色
	Math::Vector3 m_specular;	//スペキュラ色
	Math::Vector3 m_emissive;   //エミッシブ

	float m_specularPower;			//スペキュラ強さ
	uint32_t indicesNum;			//インデックス数
};