#include "CPlayer.h"
#include "Utility/DebugOutput/Debug.h"
#include "CSpriteComponent.h"


CPlayer::CPlayer()
{
	Debug::Log("init player class!\n");

	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\birb.dds");
	sprite->SetRenderRect(XMUINT2(128, 128));
	sprite->SetSpriteSize(XMUINT2(128, 128));

	colComponent = new CollisionComponent("Player");

	sprite->SetTint(XMFLOAT4(float(rand() % 2 * .5), float(rand() % 2 * .5), float(rand() % 2 * .5), 0));

	if (float(rand() % 2))
		sprite->SetScale(-1, 1, 1);

	timeElapsed = float(rand() / 100);
}

// simple movement for a player
Vector3 CPlayer::Movement(float deltaTime)
{
	float move = 200.0f;
	float speed = move * deltaTime;


	return 0;
}


void CPlayer::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	const uint32_t speed = 24;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, float((int(round(timeElapsed * speed) / 5) % 2)) * 128));

	Movement(deltaTime);
}

CPlayer::~CPlayer()
{
	Debug::Log("destroy player class!\n");
}