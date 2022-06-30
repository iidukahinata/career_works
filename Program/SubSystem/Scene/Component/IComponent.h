/**
* @file    IComponent.h
* @brief
*
* @date	   2022/06/30 2022�N�x����
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

	/** 
	* �h����Ŋg������ꍇ�A�Ăяo���K�v������܂��B
	* �����Ăяo���Ȃ���΁A�ێ�����ݒ�ƈقȂ铮�������\��������B
	*/
	virtual void Active(bool active);

	/** �X�V�����ݒ� */
	void SetTickEnable(bool enable) noexcept;
	void SetTickPriority(uint32_t priority) noexcept;

	/** �e���v���[�g�^�� this �Ɠ����^�̎� true ��Ԃ��܂��B*/
	template<class T>
	bool IsSameClass() const noexcept;

	bool IsActive() const noexcept;

	Transform& GetTransform() const noexcept;

	GameObject* GetOwner() const noexcept;
	World* GetWorld() const noexcept;
	Context* GetContext() const noexcept;

protected:

	// * �R���|�[�l���g�̍X�V�������Ǘ�
	TickComponentFunction m_tickFunction;

private:

	bool m_active;

	GameObject* m_owner;
};

template<class T>
FORCEINLINE bool IComponent::IsSameClass() const noexcept
{
	return TypeInfo() == typeid(T);
}