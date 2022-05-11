/*****************************************************************//**
 * \file   CParticleEmitter.cpp
 * \brief  Allows a entity to emit particles.
 * 
 * \author Luke Whiting
 * \date   May 2022
 *********************************************************************/

#include "CParticleEmitter.h"

CParticleEmitter::CParticleEmitter() : emit(false), overallDirection(), overallVelocity(), overallLifetime(), 
										useRandDir(false), useRandLife(false), useRandVelo(false),
										randDirMin(), randDirMax(), randLifeMin(), randLifeMax(), randVeloMin(), randVeloMax(),
										overallTexturePath("N/A")
{
	shouldDraw = true;
	shouldUpdate = true;
}

CParticleEmitter::~CParticleEmitter()
{
	particles.clear();
}

/**
 * Sets the texture for the particles emitted.
 * 
 * \param path
 */
void CParticleEmitter::SetTexture(const std::string& path)
{
	overallTexturePath = path;
};

/**
 * Sets the ammount of particles in the emitter.
 * 
 * \param size
 */
void CParticleEmitter::SetSize(const int size)
{
	particles.clear();
	particles.resize(size);
	for (int i = 0; i < particles.size(); ++i)
	{
		CParticle* particle = new CParticle();
		if(overallTexturePath != "N/A")
			particle->getSpriteComponent()->LoadTexture(overallTexturePath);

		particles[i] = particle;
	}
}

/**
 * Toggles use of random direction.
 *
 * \param toggle - boolean value toggling random usage.
 * \param min - minimum random value.
 * \param max - maximum random value.
 */
void CParticleEmitter::UseRandomDirection(bool toggle, const Vector3 min, const Vector3 max)
{
	useRandDir = toggle; randDirMin = min; randDirMax = max;
}

/**
 * Toggles use of random velocity.
 *
 * \param toggle - boolean value toggling random usage.
 * \param min - minimum random value.
 * \param max - maximum random value.
 */
void CParticleEmitter::UseRandomVelocity(bool toggle, const float min, const float max)
{
	useRandVelo = toggle; randVeloMin = min; randVeloMax = max;
}

/**
 * Toggles use of random lifetime.
 * 
 * \param toggle - boolean value toggling random usage.
 * \param min - minimum random value.
 * \param max - maximum random value.
 */
void CParticleEmitter::UseRandomLifetime(bool toggle, const float min, const float max)
{
	useRandLife = toggle; randLifeMin = min; randLifeMax = max;
}

/**
 * Sets the overall particle direction.
 * 
 * \param dir
 */
void CParticleEmitter::SetDirection(const Vector3 dir)
{
	overallDirection = dir; useRandDir = false;
}

/**
 * Returns the overall particle direction.
 * 
 * \param dir
 * \return 
 */
Vector3 CParticleEmitter::GetDirection(const Vector3 dir)
{
	return overallDirection;
}

/**
 * Sets the overall particle velocity.
 * 
 * \param velo
 */
void CParticleEmitter::SetVelocity(const float velo)
{
	overallVelocity = velo; useRandVelo = false;
}

/**
 * Returns the overall particle velocity.
 * 
 * \return velocity of particle
 */
float CParticleEmitter::GetVelocity()
{
	return overallVelocity;
}

/**
 * Sets the overall particles lifetime.
 * 
 * \param life
 */
void CParticleEmitter::SetLifetime(const float life)
{
	overallLifetime = life; useRandLife = false;
}

/**
 * Returns the overall particles lifetime.
 * 
 * \return lifetime of particle
 */
float CParticleEmitter::GetLifetime()
{
	return overallLifetime;
};

/**
 * Starts the emitter that emits particles.
 * 
 */
void CParticleEmitter::Start()
{
	emit = true;
}

/**
 * Stops the emitter from emitting particles.
 * 
 */
void CParticleEmitter::Stop()
{
	emit = false;
}

/**
 * Updates the particles in the emitter (i.e. Movement and lifetime of each particle).
 * 
 * \param deltaTime
 */
void CParticleEmitter::Update(float deltaTime)
{
	if(emit)
	{
		for (auto& particle : particles)
		{
			particle->Update(deltaTime);

			if(particle->GetLifetime() < 0)
			{
				particle->SetPosition(Vector3(0, 0, 0));

				particle->SetLifetime((useRandLife) ? Math::random(int(randLifeMin), int(randLifeMax)) : overallLifetime);
				particle->SetVelocity((useRandVelo) ? Math::random(int(randVeloMin), int(randVeloMax)) : overallVelocity);
				particle->SetDirection((useRandDir) ? Vector3(float(Math::random(int(randDirMin.x), int(randDirMax.x))), 
															  float(Math::random(int(randDirMin.y), int(randDirMax.y))), 0).Normalize() : overallDirection.Normalize());
			}

			particle->SetPosition(particle->GetPosition() + (particle->GetDirection() * particle->GetVelocity()));
		}
	}
}
/**
 * Draws the particles in relation to the emitters transform.
 * 
 * \param context
 * \param parentMat
 * \param cb
 * \param constantBuffer
 */
void CParticleEmitter::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
	// Draw the sprites for the particles.
	for (auto& particle : particles)
	{
		XMFLOAT4X4 mWorld = particle->GetTransform();
		XMMATRIX childParent = XMLoadFloat4x4(&mWorld) * XMLoadFloat4x4(&parentMat);

		XMStoreFloat4x4(&mWorld, childParent);

		particle->Draw(context, mWorld, cb, constantBuffer);
	}
}
