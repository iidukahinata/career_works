/**
* @file    World.h
* @brief
*
* @date	   2022/07/06 2022年度初版
*/
#pragma once


#include "GameObject.h"
#include "SubSystem/Core/ISubsystem.h"
#include "SubSystem/JobSystem/Sync/Job.h"

typedef UniquePtr<GameObject> GameObjectPtr;

class World : public ISubsystem
{
	SUB_CLASS(World)
public:

	World();

	bool Initialize() override;
	void Shutdown() override;

	/** 未実装メソッド */
	void LoadScene(String_View sceneName, bool isAsync = false) noexcept;
	void SaveScene(String_View sceneName) noexcept;

	/** GameObject Function */
	GameObject* CreateAndAddGameObject() noexcept;
	void AddGameObject(GameObjectPtr gameObject) noexcept;
	GameObject* GetGameObjectByName(String_View name) const noexcept;
	void RemoveGameObject(GameObject* gameObject) noexcept;

	const Vector<GameObjectPtr>& GetGameObjects() noexcept;

private:

	Job m_job;

	Vector<GameObjectPtr> m_gameObjects;
};