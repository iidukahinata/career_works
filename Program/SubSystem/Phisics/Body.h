#pragma once


#include "SubSystem/Math/MathCore.h"

struct BodyDesc
{
	float mass = 1.f;
	float repulsion = 1.f;
	float frictional = 0.f;
	float resistance = 0.f;
	Math::Vector3 gravityAcceleration = { 0.f, -0.98f, 0.f };
};

class Body
{
public:

private:
};