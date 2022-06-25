/**
* @file    ComponentFactory.h
* @brief
*
* @date	   2022/06/25 2022年度初版
*/
#pragma once


#include <memory>
#include "IComponent.h"

typedef std::weak_ptr<IComponent> ComponentRef;
typedef std::shared_ptr<IComponent> ComponentPtr;

/**
* コンポーネントの生成をシステムから分離させるために作成。
* このクラスを使用しない場合、GameObjectポインタを保持しないオブジェクトデータになります。
* 新しいコンポーネントを作成した場合、下記関数内に追加していく。
*/
struct ComponentFactory
{
	static ComponentPtr Create(GameObject* gameObject, std::string_view name) noexcept;
};