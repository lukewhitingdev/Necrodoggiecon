#pragma once
#include "CEntity.h"
#include "CSpriteComponent.h"
#include "Utility\Vector3.h"

class CParticle : public CEntity
{
public:
	CParticle();
	~CParticle();

	virtual void Update(float deltaTime);
	void Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer);

	void SetLifetime(const float life) { lifetime = life; };
	float GetLifetime() { return lifetime; };

	void SetVelocity(const float velo) { velocity = velo; }
	float GetVelocity() { return velocity; };

	void SetDirection(const Vector3 dir) { direction = dir; }
	Vector3 GetDirection() { return direction; }

	CSpriteComponent* getSpriteComponent() { return sprite; }

private:
	CSpriteComponent* sprite;
	Vector3 direction;
	float lifetime;
	float velocity;
};

