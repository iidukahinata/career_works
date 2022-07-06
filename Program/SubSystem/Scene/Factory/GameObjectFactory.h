/**
* @file    GameObjectFactory.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include "../GameObject.h"

typedef std::weak_ptr<GameObject> GameObjectRef;
typedef std::shared_ptr<GameObject> GameObjectPtr;

/**
* ゲームオブジェクトの生成をシステムから分離させるために作成。
* このクラスを使用しない場合、Worldポインタを保持しないオブジェクトデータになります。
*/
struct GameObjectFactory
{
	static GameObjectPtr Create(World* world);
};