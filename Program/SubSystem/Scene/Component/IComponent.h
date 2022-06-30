/**
* @file    IComponent.h
* @brief
*
* @date	   2022/06/29 2022�N�x����
*/
#pragma once


#include "Transform.h"
#include "../TickFunction.h"
#include "SubSystem/Core/Common/Macro.h"

class Context;
class World;
class GameObject;

typedef ClassTypeData ComponentType;

class IComponent
{
	SUPER_CLASS(IComponent)

	friend struct ComponentFactory;
public:

	IComponent();

	virtual void Initialize() {}
	virtual void Remove() {}

	virtual void Update(double deltaTime) {}

	virtual void Active(bool active);
	bool IsActive() const noexcept;

	/** �e���v���[�g�^�� this �Ɠ����^�̎� true ��Ԃ��܂��B*/
	template<class T>
	bool IsSameClass() const noexcept;

	Transform& GetTransform() const noexcept;

	GameObject* GetOwner() const noexcept;
	World* GetWorld() const noexcept;
	Context* GetContext() const noexcept;

private:

	GameObject* m_owner;

	TickComponentFunction m_tickFunction;

	bool m_active;
};

template<class T>
FORCEINLINE bool IComponent::IsSameClass() const noexcept
{
	return TypeInfo() == typeid(T);
}