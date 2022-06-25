/**
* @file    IComponent.h
* @brief
*
* @date	   2022/06/25 2022年度初版
*/
#pragma once


#include <string_view>
#include "SubSystem/Core/Common/Macro.h"

class GameObject;

/* Component 派生クラスで必ず定義するマクロ定義 */
#define COMPONENT_CLASS(CLASS, NAME)							\
SUB_CLASS(CLASS)												\
static INLINE ComponentType Type##CLASS = ComponentType(#NAME); \
const ComponentType& GetType() override							\
{																\
	return Type##CLASS;											\
}

/**
* 名前から ComponentType を識別するために作成。
*/
struct ComponentType
{
	const uint32_t Hash;
	const std::string_view Str;

	constexpr ComponentType(std::string_view name) : Hash(GetHashFromCRC(name)), Str(name)
	{}

	bool operator==(const ComponentType& componentType) const
	{
		return Hash == componentType.Hash;
	}
};

class IComponent
{
	SUPER_CLASS(IComponent)

	friend struct ComponentFactory;
public:

	virtual const ComponentType& GetType();

	/* 指定オブジェクトが this と同じ型の時 true を返します。*/
	template<class T>
	bool IsSameClass(T* obj) const noexcept;

	/* テンプレート型が this と同じ型の時 true を返します。*/
	template<class T>
	bool IsSameClass() const noexcept;

	GameObject* GetOwner() const noexcept;

private:

	GameObject* m_owner;
};

template<class T>
FORCEINLINE bool IComponent::IsSameClass(T* obj) const noexcept
{
	if (obj)
	{
		return TypeInfo() == obj->TypeInfo();
	}
	return false;
}

template<class T>
FORCEINLINE bool IComponent::IsSameClass() const noexcept
{
	return TypeInfo() == typeid(T);
}