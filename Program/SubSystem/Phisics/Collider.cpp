

#include "Collider.h"
#include <btBulletCollisionCommon.h>
#include "Body.h"
#include "SubSystem/Scene/GameObject.h"
#include "SubSystem/Tools/Chack.h"

void Collider::Init(Transform* parent, Body* body)
{
	Chack(parent, "parent ��	 nullptr ���w�肷�邱�Ƃ͏o���܂���B");
	Chack(body, "body ��	 nullptr ���w�肷�邱�Ƃ͏o���܂���B");

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