#include "CParticle.h"

CParticle::CParticle() : lifetime(0), velocity(0)
{
	sprite = new CSpriteComponent();
	if(FAILED(sprite->LoadTexture("Resources/arrow.dds")))
		throw;
	sprite->SetScale(0.1, 0.1, 0.1);
}

CParticle::~CParticle()
{
	delete sprite;
	sprite = nullptr;
}

/**
 * Updates the particles lifetime and velocity.
 * 
 * \param deltaTime
 */
void CParticle::Update(float deltaTime)
{
	lifetime -= deltaTime;
	velocity -= deltaTime;

	if (velocity < 0)
		velocity = 0;

	sprite->Update(deltaTime);
}

/**
 * Draws the particle.
 * 
 * \param context
 * \param parentMat
 * \param cb
 * \param constantBuffer
 */
void CParticle::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
	sprite->Draw(context, parentMat, cb, constantBuffer);
}

/**
 * Sets the lifetime of the particle.
 * 
 * \param life the lifetime of the particle
 */
void CParticle::SetLifetime(const float life)
{
	lifetime = life;
}

/**
 * Returns the lifetime of the particle.
 * 
 * \return the lifetime of the particle.
 */
float CParticle::GetLifetime()
{
	return lifetime;
}

/**
 * Sets the velocity of the particle.
 * 
 * \param velo the velocity of the particle.
 */
void CParticle::SetVelocity(const float velo)
{
	velocity = velo;
}

/**
 * Returns the velocity of the particle.
 * 
 * \return the velocity of the particle.
 */
float CParticle::GetVelocity()
{
	return velocity;
}

/**
 * Sets the direction of the particle.
 * 
 * \param dir the direction of the particle.
 */
void CParticle::SetDirection(const Vector3 dir)
{
	direction = dir;
}

/**
 * Returns the direction of the particle.
 * 
 * \return the direction of the particle.
 */
Vector3 CParticle::GetDirection()
{
	return direction;
}

/**
 * Returns the sprite component of the particle.
 * 
 * \return the sprite component of the particle.
 */
CSpriteComponent* CParticle::getSpriteComponent()
{
	return sprite;
}
