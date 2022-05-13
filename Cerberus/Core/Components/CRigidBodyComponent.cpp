#include "CRigidBodyComponent.h"
#include "Cerberus/Core/CEntity.h"

CRigidBodyComponent::CRigidBodyComponent() : acceleration(), velocity(), damping(0.5f)
{
}

CRigidBodyComponent::~CRigidBodyComponent()
{
}

static Vector3 pos;
void CRigidBodyComponent::Update(float deltaTime)
{
	pos += velocity * deltaTime;							// Velocity Step
	pos += acceleration * deltaTime * deltaTime * 0.5f;		// Acceleration Step
	this->GetParent()->SetPosition(pos);

	velocity *= damping * deltaTime;
}

void CRigidBodyComponent::SetVelocity(const Vector3& velo)
{
	velocity = velo;
}

Vector3& CRigidBodyComponent::GetVelocity()
{
	return velocity;
}

void CRigidBodyComponent::SetAcceleration(const Vector3& accel)
{
	acceleration = accel;
}

Vector3& CRigidBodyComponent::GetAcceleration()
{
	return acceleration;
}
