/**
* @file    IComponent.h
* @brief
*
* @date	   2022/06/30 2022年度初版
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
	* 派生先で拡張する場合、呼び出す必要があります。
	* もし呼び出さなければ、保持する設定と異なる動作をする可能性がある。
	*/
	virtual void Active(bool active);

	/** 更新処理設定 */
	void SetTickEnable(bool enable) noexcept;
	void SetTickPriority(uint32_t priority) noexcept;

	/** テンプレート型が this と同じ型の時 true を返します。*/
	template<class T>
	bool IsSameClass() const noexcept;

	bool IsActive() const noexcept;

	Transform& GetTransform() const noexcept;

	GameObject* GetOwner() const noexcept;
	World* GetWorld() const noexcept;
	Context* GetContext() const noexcept;

protected:

	// * コンポーネントの更新処理を管理
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