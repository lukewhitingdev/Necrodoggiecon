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

void CParticleEmitter::Start()
{
	emit = true;
}

void CParticleEmitter::Stop()
{
	emit = false;
}

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

				particle->SetLifetime((useRandLife) ? random(randLifeMin, randLifeMax) : overallLifetime);
				particle->SetVelocity((useRandVelo) ? random(randVeloMin, randVeloMax) : overallVelocity);
				particle->SetDirection((useRandDir) ? Vector3(random(randDirMin.x, randDirMax.x), random(randDirMin.y, randDirMax.y), 0).Normalize() : overallDirection.Normalize());
			}

			particle->SetPosition(particle->GetPosition() + (particle->GetDirection() * particle->GetVelocity()));
		}
	}
}

void CParticleEmitter::Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
{
	// Draw the sprites for the particles.
	for (auto& particle : particles)
	{
		XMFLOAT4X4 world = particle->GetTransform();
		XMMATRIX childParent = XMLoadFloat4x4(&world) * XMLoadFloat4x4(&parentMat);

		XMStoreFloat4x4(&world, childParent);

		particle->Draw(context, world, cb, constantBuffer);
	}
}
