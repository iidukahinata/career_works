/**
* @file    GameObject.cpp
* @brief   各GameObjectの抽象クラス
*
* @date	   2022/04/30 2022年度初版
* @author  飯塚陽太
*/


#include "GameObject.h"

int IGameObject::GetID() const noexcept
{
	return m_id;
}

void IGameObject::SetID(int id) noexcept
{
	m_id = id;
}

Transform& IGameObject::GetTransform() noexcept
{
	return m_transform;
}

void IGameObject::SetScene(IScene* scene) noexcept
{
	assert(!m_scene);
	m_scene = scene;
}