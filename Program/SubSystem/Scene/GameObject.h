/**
* @file    GameObject.h
* @brief
*
* @date	   2022/06/29 2022年度初版
*/
#pragma once


#include <map>
#include <memory>
#include "Component/IComponent.h"
#include "Component/Transform.h"

class GameObject
{
	CLASS_DATA(GameObject)

	friend struct GameObjectFactory;
public:

	/** 指定名コンポーネントの追加。指定名が存在しない等の場合、null を返す。*/
	IComponent* AddComponent(std::string_view name) noexcept;
	void AddComponent(IComponent* component) noexcept;

	/** 保持するコンポーネントを消去するため、そのアドレスを引数とする。*/
	void RemoveComponent(IComponent* component) noexcept;

	/** 型名からコンポーネントを検索。*/
	template<class T>
	T* GetComponent();

	/** 指定名コンポーネントを保持する場合、そのアドレスを返す。*/
	IComponent* FindComponent(std::string_view name) noexcept;

	void Active(bool active) noexcept;

	/** 各GameObject識別用に使用。*/
	void SetName(std::string_view name) noexcept;
	const std::string& GetName() const noexcept;

	/** Worldクラスで以外で使用されると、場合によってはScene終了時までメモリが解放されず残り続けます。*/
	void SetID(uint32_t id) noexcept;
	uint32_t GetID() const noexcept;

	Transform& GetTransform() noexcept;

	World* GetOwner() const noexcept;
	Context* GetContext() const noexcept;

private:

	// * 所属ワールドクラスを保持。
	World* m_owner;

	// * WorldクラスでのID値
	uint32_t m_id;

	// * Worldクラスで探索時等に使用される。
	std::string m_name;

	Transform m_transform;

	// * -> ハッシュ値 : 各コンポーネントオブジェクト
	std::map<uint32_t, std::unique_ptr<IComponent>> m_components;
};

template<class T>
FORCEINLINE T* GameObject::GetComponent()
{
	return dynamic_cast<T*>(FindComponent(T::TypeData.Name));
}