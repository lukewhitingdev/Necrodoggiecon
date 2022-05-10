#pragma once
#include "CComponent.h"
#include "CEntity.h"
#include "Entities/CParticle.h"
#include "Utility/Math/Math.h"

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
	Vector3 GetDirection(const Vector3 dir);

	void SetVelocity(const float velo);
	float GetVelocity(const float velo);

	void SetLifetime(const float life);
	float GetLifetime(const float velo);

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

