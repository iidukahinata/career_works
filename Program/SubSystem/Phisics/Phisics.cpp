

#include "Phisics.h"
#include <btBulletDynamicsCommon.h>

void Phisics::Init() noexcept
{
	m_broadhase = std::make_unique<btDbvtBroadphase>();
	m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
	m_dispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());
	m_constraintSolver = std::make_unique<btSequentialImpulseConstraintSolver>();
	m_world = std::make_unique<btDiscreteDynamicsWorld>(m_dispatcher.get(), m_broadhase.get(), m_constraintSolver.get(), m_collisionConfiguration.get());

	m_world->setGravity(btVector3(0.f, -9.81f, 0.f));
}

void Phisics::Update(float deltaTime) noexcept
{
	m_world->stepSimulation(deltaTime);
}

btDiscreteDynamicsWorld* Phisics::GetWorld() const noexcept
{
	return m_world.get();
}