/**
* @file    GameObjectFactory.cpp
* @brief
*
* @date	   2022/06/25 2022îNìxèâî≈
*/


#include "GameObjectFactory.h"

GameObjectPtr GameObjectFactory::Create(World* world)
{
	GameObjectPtr gameObject = std::make_shared<GameObject>();
	gameObject->m_owner = world;
	gameObject->m_id = 0;
	gameObject->m_name = "GameObject";
	return gameObject;
}