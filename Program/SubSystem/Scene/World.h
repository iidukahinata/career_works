/**
* @file    World.h
* @brief
*
* @date	   2022/06/24 2022年度初版
*/
#pragma once


#include <span>
#include <vector>
#include "GameObjectFactory.h"
#include "SubSystem/Core/ISubsystem.h"

class World : public ISubsystem
{
	SUB_CLASS(World)
public:

	bool Initialize() override;

	/** 未実装メソッド */
	void LoadScene(std::string_view sceneName, bool isAsync = false) noexcept;
	void SaveScene(std::string_view sceneName) noexcept;

	/** GameObject Function */
	GameObjectRef CreateAndAddGameObject() noexcept;
	void AddGameObject(GameObjectPtr gameObject) noexcept;
	GameObjectRef GetGameObjectByName(std::string_view name) const noexcept;
	void RemoveGameObject(GameObject* gameObject) noexcept;

	std::span<const GameObjectPtr> GetGameObjects() const noexcept;

private:

	std::vector<GameObjectPtr> m_gameObjects;
};