#pragma once
#include "CComponent.h"
#include "CEntity.h"
#include "Entities/CParticle.h"

#include <vector>

class CParticleEmitter : public CComponent
{
public:
	CParticleEmitter();
	~CParticleEmitter();

	void SetTexture(const std::string& path) { overallTexturePath = path; };
	void SetSize(const int size);

	void UseRandomDirection(bool toggle, const Vector3 min, const Vector3 max) { useRandDir = toggle; randDirMin = min; randDirMax = max; };
	void UseRandomVelocity(bool toggle, const float min, const float max) { useRandVelo = toggle; randVeloMin = min; randVeloMax = max; };
	void UseRandomLifetime(bool toggle, const float min, const float max) { useRandLife = toggle; randLifeMin = min; randLifeMax = max; };

	void SetDirection(const Vector3 dir) { overallDirection = dir; useRandDir = false; };
	Vector3 GetDirection(const Vector3 dir) { return overallDirection; };

	void SetVelocity(const float velo) { overallVelocity = velo; useRandVelo = false; };
	float GetVelocity(const float velo) { return overallVelocity; };

	void SetLifetime(const float life) { overallLifetime = life; useRandLife = false;};
	float GetLifetime(const float velo) { return overallLifetime; };

	void Start();
	void Stop();

	//Updated automatically every single frame
	virtual void Update(float deltaTime);
	virtual void Draw(struct ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer);

private:

	// TODO: REPLACE THIS WITH A PROPER MATHS ONE THAT CAN ACCEPT NEGATIVE MINS AND MAX'S
	int random(int min, int max)
	{
		return min + (rand() % static_cast<int>(max - min + 1));
	}

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

