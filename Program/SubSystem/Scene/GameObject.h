/**
* @file    GameObject.h
* @brief
*
* @date	   2022/06/24 2022�N�x����
*/
#pragma once


#include <map>
#include <memory>
#include "Component/IComponent.h"
#include "Component/Components/Transform.h"

class Context;
class World;

class GameObject
{
	friend struct GameObjectFactory;
public:

	/** �w�薼�R���|�[�l���g�̒ǉ��B�w�薼�����݂��Ȃ����̏ꍇ�Anull ��Ԃ��B*/
	IComponent* AddComponent(std::string_view name) noexcept;

	/** �ێ�����R���|�[�l���g���������邽�߁A���̃A�h���X�������Ƃ���B*/
	void RemoveComponent(IComponent* component) noexcept;

	/** �^������R���|�[�l���g�������B*/
	template<class T>
	T* GetComponent();

	/** �w�薼�R���|�[�l���g��ێ�����ꍇ�A���̃A�h���X��Ԃ��B */
	IComponent* FindComponent(std::string_view name) const noexcept;

	/* �eGameObject���ʗp�Ɏg�p�B*/
	void SetName(std::string_view name) noexcept;
	std::string_view GetName() const noexcept;

	/** World�N���X�ňȊO�Ŏg�p�����ƁA�ꍇ�ɂ���Ă�Scene�I�����܂Ń�������������ꂸ�c�葱���܂��B*/
	void SetID(uint32_t id) noexcept;
	uint32_t GetID() const noexcept;

	World* GetOwner() const noexcept;
	Context* GetContext() const noexcept;

private:

	/* �������[���h�N���X��ێ��B*/
	World* m_owner;

	// * World�N���X�ł�ID�l
	uint32_t m_id;

	// * World�N���X�ŒT�������Ɏg�p�����
	std::string_view m_name;

	// * -> �n�b�V���l : �e�R���|�[�l���g�I�u�W�F�N�g
	std::map<uint32_t, std::shared_ptr<IComponent>> m_components;
};

template<class T>
FORCEINLINE T* GameObject::GetComponent()
{
	for (auto& component : m_components)
	{
		if (component.second->IsSameClass<T>())
		{
			return dynamic_cast<T*>(component.second.get());
		}
	}
	return nullptr;
}