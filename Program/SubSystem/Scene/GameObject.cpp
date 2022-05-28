/**
* @file    GameObject.cpp
* @brief   �eGameObject�̒��ۃN���X
*
* @date	   2022/04/30 2022�N�x����
* @author  �ђ˗z��
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