#pragma once


#include <memory>
#include "SubSystem/Math/MathCore.h"
#include "SubSystem/Scene/Transform.h"

struct BodyDesc
{
	float mass = 1.f;
	float repulsion = 1.f;
	float frictional = 0.f;
	float resistance = 0.f;
	Math::Vector3 gravityAcceleration = { 0.f, -0.98f, 0.f };
};

enum ForceMode
{
	Force,
	Impulse
};

class Body
{
public:

	~Body();

	void Init(Transform* parent, const BodyDesc& bodyDesc) noexcept;
	void Update() noexcept;

	void SetMass(float mass) noexcept;

	const Math::Vector3& GetVelocity() const noexcept;
	void SetVelocity(const Math::Vector3& velocity) noexcept;

	void AddForce(const Math::Vector3& force, ForceMode mode) noexcept;
	void ClearForces() const noexcept;

	void Active(bool isActive) const noexcept;

	void SetCollision(class btCollisionShape* shape) noexcept;

	class btRigidBody* GetRigidBody() const noexcept;
	Transform* GetParent() const noexcept;

private:

	void Relese() noexcept;

private:

	Transform* m_parent;
	btCollisionShape* m_collisionShape;

	std::unique_ptr<class btRigidBody> m_rigidBody;
};