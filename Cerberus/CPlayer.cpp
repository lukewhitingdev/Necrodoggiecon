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

	sprite->SetTint(XMFLOAT4(float(rand() % 2 * .5), float(rand() % 2 * .5), float(rand() % 2 * .5), 0));

	if (float(rand() % 2))
		sprite->SetScale(-1, 1, 1);

	timeElapsed = float(rand() / 100);
}


void CPlayer::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	const uint32_t speed = 24;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, float((int(round(timeElapsed * speed) / 5) % 2)) * 128));
}

CPlayer::~CPlayer()
{
	Debug::Log("destroy player class!\n");
}