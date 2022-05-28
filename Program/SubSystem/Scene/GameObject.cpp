/**
* @file    GameObject.cpp
* @brief   �eGameObject�̒��ۃN���X
*
* @date	   2022/05/28 2022�N�x����
* @author  �ђ˗z��
*/


#include "GameObject.h"
#include "SubSystem/Tools/Chack.h"

int IGameObject::GetID() const noexcept
{
	return m_id;
}

void IGameObject::SetID(int id) noexcept
{
	Chack(id >= 0);
	m_id = id;
}

Transform& IGameObject::GetTransform() noexcept
{
	return m_transform;
}

void IGameObject::SetScene(IScene* scene) noexcept
{
	Chack(!m_scene);
	m_scene = scene;
}