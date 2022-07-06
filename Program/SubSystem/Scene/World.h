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
	void AddGameObject(UniquePtr<GameObject> gameObject) noexcept;
	GameObject* GetGameObjectByName(String_View name) const noexcept;
	void RemoveGameObject(GameObject* gameObject) noexcept;

	const Vector<UniquePtr<GameObject>>& GetGameObjects() noexcept;

private:

	Job m_job;

	Vector<UniquePtr<GameObject>> m_gameObjects;
};