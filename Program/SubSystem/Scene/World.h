/**
* @file    World.h
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/
#pragma once


#include <span>
#include "GameObject.h"
#include "SubSystem/Core/ISubsystem.h"
#include "SubSystem/JobSystem/Sync/Job.h"

typedef std::weak_ptr<GameObject> GameObjectRef;
typedef std::shared_ptr<GameObject> GameObjectPtr;

class World : public ISubsystem
{
	SUB_CLASS(World)
public:

	World();

	bool Initialize() override;
	void Shutdown() override;

	/** ���������\�b�h */
	void LoadScene(String_View sceneName, bool isAsync = false) noexcept;
	void SaveScene(String_View sceneName) noexcept;

	/** GameObject Function */
	GameObjectRef CreateAndAddGameObject() noexcept;
	void AddGameObject(GameObjectPtr gameObject) noexcept;
	GameObjectRef GetGameObjectByName(String_View name) const noexcept;
	void RemoveGameObject(GameObject* gameObject) noexcept;

	const Vector<GameObjectPtr>& GetGameObjects() noexcept;

private:

	Job m_job;

	Vector<GameObjectPtr> m_gameObjects;
};