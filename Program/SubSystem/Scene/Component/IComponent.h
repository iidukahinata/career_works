/**
* @file    IComponent.h
* @brief
*
* @date	   2022/06/25 2022�N�x����
*/
#pragma once


#include <string_view>
#include "SubSystem/Core/Common/Macro.h"

class GameObject;

/* Component �h���N���X�ŕK����`����}�N����` */
#define COMPONENT_CLASS(CLASS, NAME)							\
SUB_CLASS(CLASS)												\
static INLINE ComponentType Type##CLASS = ComponentType(#NAME); \
const ComponentType& GetType() override							\
{																\
	return Type##CLASS;											\
}

/**
* ���O���� ComponentType �����ʂ��邽�߂ɍ쐬�B
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

	/* �w��I�u�W�F�N�g�� this �Ɠ����^�̎� true ��Ԃ��܂��B*/
	template<class T>
	bool IsSameClass(T* obj) const noexcept;

	/* �e���v���[�g�^�� this �Ɠ����^�̎� true ��Ԃ��܂��B*/
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