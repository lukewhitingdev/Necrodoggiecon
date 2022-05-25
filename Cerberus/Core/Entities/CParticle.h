/*****************************************************************//**
 * \file   CParticle.cpp
 * \brief  A helper class for the ParticleEmitter, encapsulates a singluar particle that is emitted.
 *
 * \author Luke Whiting
 * \date   May 2022
 *********************************************************************/
#pragma once
#include "Cerberus/Core/CEntity.h"
#include "Cerberus/Core/Components/CSpriteComponent.h"
#include "Cerberus/Core/Utility/Vector3.h"

class CParticle : public CEntity
{
public:
	CParticle();
	~CParticle();

	virtual void Update(float deltaTime);
	void Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer);

	void SetLifetime(const float life);
	float GetLifetime();

	void SetVelocity(const float velo);
	float GetVelocity();

	void SetDirection(const Vector3 dir);
	Vector3 GetDirection();

	CSpriteComponent* getSpriteComponent();

private:
	CSpriteComponent* sprite;
	Vector3 direction;
	float lifetime;
	float velocity;
};

