#include "AlarmEnemy.h"

AlarmEnemy::AlarmEnemy()
{
	sprite->LoadTexture("Resources\\MageEnemy.dds");
	sprite->SetRotation(1.5708f);
	sprite->SetRenderRect(XMUINT2(64, 64));
	sprite->SetSpriteSize(XMUINT2(64, 64));
	sprite->SetScale(Vector3{ 2.0f, 2.0f, 1.0f });

	loadNoise = AddComponent<CAudioEmitterComponent>();
	loadNoise->Load("Resources/TestShortAudio.wav");

	loadNoise->SetRange(10000.0f);
}

void AlarmEnemy::Update(float deltaTime)
{
	if (alarmTimer > 0.0f)
	{
		alarmTimer -= 0.016f;
		// If the timer is up then go back to pathfinding.
		if (alarmTimer < 0.02f)
		{
			onCooldown = false;
		}

	}

	CAIController::Update(deltaTime);
}

void AlarmEnemy::ChasePlayer(CCharacter* player)
{
	if (!onCooldown)
	{
		loadNoise->Play();
		alarmTimer = 10.0f;
		onCooldown = true;
	}
}

void AlarmEnemy::ChaseEnter()
{
}
