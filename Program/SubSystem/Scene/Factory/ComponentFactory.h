/**
* @file    ComponentFactory.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include "../Component/IComponent.h"

/**
* コンポーネントの生成をシステムから分離させるために作成。
* このクラスを使用しない場合、GameObjectポインタを保持しないオブジェクトデータになります。
* 新しいコンポーネントを作成した場合、下記関数内に追加していく。
*/
struct ComponentFactory
{
	static UniquePtr<IComponent> Create(GameObject* gameObject, StringView name) noexcept;
};