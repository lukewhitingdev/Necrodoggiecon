#include "CPlayer.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"
#include "Cerberus\Core\Components\CSpriteComponent.h"


CPlayer::CPlayer()
{
	Debug::Log("init player class!\n");

	sprite = AddComponent<CSpriteComponent>(NAME_OF(sprite));
	sprite->LoadTexture("Resources/Game/birb.dds");
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