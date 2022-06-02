

#include "Body.h"
#include "Phisics.h"
#include "PhisicsHelper.h"
#include <btBulletDynamicsCommon.h>

class MotionState : public btMotionState
{
public:

	Body* m_body;
	btTransform m_graphicsWorldTrans;
	btTransform m_centerOfMassOffset;
	btTransform m_startWorldTrans;
	void* m_userPointer;

	BT_DECLARE_ALIGNED_ALLOCATOR();

	MotionState(const btTransform& startTrans = btTransform::getIdentity(), const btTransform& centerOfMassOffset = btTransform::getIdentity())
		: m_graphicsWorldTrans(startTrans),
		m_centerOfMassOffset(centerOfMassOffset),
		m_startWorldTrans(startTrans),
		m_userPointer(0)
	{
	}

	MotionState(Body* body)
		: m_body(body)
	{
	}

	///synchronizes world transform from user to physics
	virtual void getWorldTransform(btTransform& centerOfMassWorldTrans) const
	{
		centerOfMassWorldTrans = m_graphicsWorldTrans * m_centerOfMassOffset.inverse();
	}

	//virtual void getWorldTransform(btTransform& centerOfMassWorldTrans) const
	//{
	//	auto origin = ToBtVector3(m_body->GetParent()->GetWoldPosition());
	//	auto rotation = ToBtQuaternion(Math::Vector4(m_body->GetParent()->GetRotation(), 1.f));
	//
	//	centerOfMassWorldTrans.setOrigin(origin);
	//	centerOfMassWorldTrans.setRotation(rotation);
	//}

	///synchronizes world transform from physics to user
	///Bullet only calls the update of worldtransform for active objects
	virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans)
	{
		m_graphicsWorldTrans = centerOfMassWorldTrans * m_centerOfMassOffset;
	}

	//virtual void setWorldTransform(const btTransform& centerOfMassWorldTrans)
	//{
	//	auto rot = worldTrans.getRotation();
	//	worldTrans.getOrigin() - rot * m_body->GetColliderCenter();
	//}
};

Body::~Body()
{
	Relese();
}

void Body::Init(Transform* parent, const BodyDesc& bodyDesc) noexcept
{
	Chack(parent, "parent Ç…	 nullptr ÇéwíËÇ∑ÇÈÇ±Ç∆ÇÕèoóàÇ‹ÇπÇÒÅB");

	m_parent = parent;

	btVector3 inertia(0, 0, 0);

	MotionState* motionState = new MotionState();
	btRigidBody::btRigidBodyConstructionInfo constructionInfo(bodyDesc.mass, motionState, nullptr, inertia);

	m_rigidBody = std::make_unique<btRigidBody>(constructionInfo);

	Phisics::Get().GetWorld()->addRigidBody(m_rigidBody.get());
}

void Body::Update() noexcept
{
}

void Body::SetMass(float mass) noexcept
{
}

const Math::Vector3& Body::GetVelocity() const noexcept
{
	return ToVector3(m_rigidBody->getAngularVelocity());
}

void Body::SetVelocity(const Math::Vector3& velocity) noexcept
{
	m_rigidBody->setAngularVelocity(ToBtVector3(velocity));
}

void Body::AddForce(const Math::Vector3& force, ForceMode mode) noexcept
{
	if (mode == Force)
	{
		m_rigidBody->applyCentralForce(ToBtVector3(force));
	}
	else if (mode == Impulse)
	{
		m_rigidBody->applyCentralImpulse(ToBtVector3(force));
	}
}

void Body::ClearForces() const noexcept
{
	m_rigidBody->clearForces();
}

void Body::Active(bool isActive) const noexcept
{
	m_rigidBody->activate(isActive);
}

void Body::SetCollision(btCollisionShape* shape) noexcept
{
	m_collisionShape = shape;
}

btRigidBody* Body::GetRigidBody() const noexcept
{
	return m_rigidBody.get();
}

Transform* Body::GetParent() const noexcept
{
	return m_parent;
}

void Body::Relese() noexcept
{
	Phisics::Get().GetWorld()->removeRigidBody(m_rigidBody.get());
}