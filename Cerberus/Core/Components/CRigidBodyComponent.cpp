/*****************************************************************//**
 * \file   CRigidBodyComponent.cpp
 * \brief  Adds basic rigid body physics to a entity.
 * 
 * \author Luke Whiting
 * \date   Jan 2022
 *********************************************************************/

#include "CRigidBodyComponent.h"
#include "Cerberus/Core/CEntity.h"

CRigidBodyComponent::CRigidBodyComponent() : acceleration(), velocity(), damping(0.5f)
{
}

CRigidBodyComponent::~CRigidBodyComponent()
{
}


static Vector3 pos;
/**
 * Updates the integration for the rigid body system.
 * 
 * \param deltaTime
 */
void CRigidBodyComponent::Update(float deltaTime)
{
	pos += velocity * deltaTime;							// Velocity Step
	pos += acceleration * deltaTime * deltaTime * 0.5f;		// Acceleration Step
	this->GetParent()->SetPosition(pos);

	velocity *= damping * deltaTime;
}

/**
 * Sets the velocity of the rigidbody.
 * 
 * \param velo
 */
void CRigidBodyComponent::SetVelocity(const Vector3& velo)
{
	velocity = velo;
}

/**
 * Returns the current velocity of the rigidbody.
 * 
 * \return 
 */
Vector3& CRigidBodyComponent::GetVelocity()
{
	return velocity;
}

/**
 * Sets the acceleration of the rigidbody.
 * 
 * \param accel
 */
void CRigidBodyComponent::SetAcceleration(const Vector3& accel)
{
	acceleration = accel;
}

/**
 * Returns the current acceleration of the rigidbody.
 * 
 * \return 
 */
Vector3& CRigidBodyComponent::GetAcceleration()
{
	return acceleration;
}
