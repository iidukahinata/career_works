/**
* @file    World.h
* @brief
*
* @date	   2022/06/30 2022年度初版
*/
#pragma once


#include <span>
#include <vector>
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

	/** 未実装メソッド */
	void LoadScene(std::string_view sceneName, bool isAsync = false) noexcept;
	void SaveScene(std::string_view sceneName) noexcept;

	/** GameObject Function */
	GameObjectRef CreateAndAddGameObject() noexcept;
	void AddGameObject(GameObjectPtr gameObject) noexcept;
	GameObjectRef GetGameObjectByName(std::string_view name) const noexcept;
	void RemoveGameObject(GameObject* gameObject) noexcept;

	const std::vector<GameObjectPtr>& GetGameObjects() noexcept;

private:

	Job m_job;

	std::vector<GameObjectPtr> m_gameObjects;
};