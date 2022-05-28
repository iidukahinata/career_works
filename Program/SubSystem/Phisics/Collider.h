#pragma once


#include <memory>
#include "SubSystem/Math/Vector3.h"
#include "SubSystem/Scene/Transform.h"

class Collider
{
public:

	void Init(Transform* parent, class Body* body);

	const Math::Vector3& GetCentor() const noexcept;
	void SetCentor(const Math::Vector3& center) noexcept;

private:

	Transform* m_parent;
	class Body* m_body;

	std::unique_ptr<class btCollisionShape> m_shape;

	Math::Vector3 m_center;
};