/**
* @file    GameObjectFactory.cpp
* @brief
*
* @date	   2022/07/06 2022îNìxèâî≈
*/


#include "GameObjectFactory.h"

UniquePtr<GameObject> GameObjectFactory::Create(World* world)
{
	UniquePtr<GameObject> gameObject = MakeUnique<GameObject>();
	gameObject->m_owner = world;
	gameObject->m_id = 0;
	gameObject->m_name = "GameObject";
	return gameObject;
}