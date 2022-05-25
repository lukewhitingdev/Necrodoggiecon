/*****************************************************************//**
 * \file   CParticleEmitter.cpp
 * \brief  Allows a entity to emit particles.
 *
 * \author Luke Whiting
 * \date   May 2022
 *********************************************************************/
#pragma once
#include "Cerberus/Core/CComponent.h"
#include "Cerberus/Core/CEntity.h"
#include "Cerberus/Core/Entities/CParticle.h"
#include "Cerberus/Core/Utility/Math/Math.h"
#include <vector>

class CParticleEmitter : public CComponent
{
public:
	CParticleEmitter();
	~CParticleEmitter();
	
	void SetTexture(const std::string& path);
	void SetSize(const int size);

	void UseRandomDirection(bool toggle, const Vector3 min, const Vector3 max);
	void UseRandomVelocity(bool toggle, const float min, const float max);
	void UseRandomLifetime(bool toggle, const float min, const float max);

	void SetDirection(const Vector3 dir);
	Vector3 GetDirection();

	void SetVelocity(const float velo);
	float GetVelocity();

	void SetLifetime(const float life);
	float GetLifetime();

	void Start();
	void Stop();

	//Updated automatically every single frame
	virtual void Update(float deltaTime);
	virtual void Draw(struct ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer);

private:

	std::vector<CParticle*> particles;
	bool emit;


	// Set Overall Variables.
	Vector3 overallDirection;
	float overallVelocity;
	float overallLifetime;
	std::string overallTexturePath;

	// Random Variables
	bool useRandDir;
	bool useRandVelo;
	bool useRandLife;

	Vector3 randDirMin;
	Vector3 randDirMax;

	float randVeloMin;
	float randVeloMax;

	float randLifeMin;
	float randLifeMax;
};

