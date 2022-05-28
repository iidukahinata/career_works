

#include "Collider.h"
#include <btBulletCollisionCommon.h>
#include "Body.h"
#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Tools/Chack.h"

void Collider::Init(Transform* parent, Body* body)
{
	Chack(parent, "parent に	 nullptr を指定することは出来ません。");
	Chack(body, "body に	 nullptr を指定することは出来ません。");

	m_parent = parent;
	m_body = body;
}

const Math::Vector3& Collider::GetCentor() const noexcept
{
	return m_center;
}

void Collider::SetCentor(const Math::Vector3& center) noexcept
{
	if (m_center == center)
	{
		return;
	}

	m_center = center;
	m_body->SetCollision(m_shape.get());
}