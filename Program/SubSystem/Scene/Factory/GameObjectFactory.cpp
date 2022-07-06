/**
* @file    GameObjectFactory.cpp
* @brief
*
* @date	   2022/07/06 2022�N�x����
*/


#include "GameObjectFactory.h"

GameObjectPtr GameObjectFactory::Create(World* world)
{
	GameObjectPtr gameObject = MakeUnique<GameObject>();
	gameObject->m_owner = world;
	gameObject->m_id = 0;
	gameObject->m_name = "GameObject";
	return gameObject;
}