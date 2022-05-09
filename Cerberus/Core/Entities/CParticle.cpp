#include "CParticle.h"

CParticle::CParticle() : lifetime(0), velocity(0)
{
	sprite = new CSpriteComponent();
	if(FAILED(sprite->LoadTexture("Resources\\arrow.dds")))
		throw;
	sprite->SetScale(0.1, 0.1, 0.1);
}

CParticle::~CParticle()
{
	delete sprite;
	sprite = nullptr;
}

void CParticle::Update(float deltaTime)
{
	lifetime -= deltaTime;
	velocity -= deltaTime;

	if (velocity < 0)
		velocity = 0;

	sprite->Update(deltaTime);
}

void CParticle::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
	sprite->Draw(context, parentMat, cb, constantBuffer);
}
