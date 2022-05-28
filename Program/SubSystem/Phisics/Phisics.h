#pragma once


#include <memory>
#include <vector>
#include "Body.h"

class Phisics
{
public:

	static Phisics& Get() noexcept
	{
		static Phisics instance;
		return instance;
	}

	void Init() noexcept;
	void Update(float deltaTime) noexcept;

	class btDiscreteDynamicsWorld* GetWorld() const noexcept;

private:

	std::unique_ptr<class btDbvtBroadphase>					   m_broadhase = nullptr;
	std::unique_ptr<class btDefaultCollisionConfiguration>	   m_collisionConfiguration = nullptr;
	std::unique_ptr<class btCollisionDispatcher>			   m_dispatcher = nullptr;
	std::unique_ptr<class btSequentialImpulseConstraintSolver> m_constraintSolver = nullptr;
	std::unique_ptr<class btDiscreteDynamicsWorld>			   m_world = nullptr;

	std::vector<Body*> m_bodys;
};