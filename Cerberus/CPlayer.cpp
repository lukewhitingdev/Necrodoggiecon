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

	sprite->SetTint(XMFLOAT4(rand() % 2 * .5, rand() % 2 * .5, rand() % 2 * .5, 0));

	if (rand() % 2)
		sprite->SetScale(-1, 1, 1);

	timeElapsed = rand() / 100;
}

// simple movement for a player
Vector3 CPlayer::Movement(float deltaTime)
{
	float move = 200.0f;
	float speed = move * deltaTime;



	if (GetAsyncKeyState(0x44))
	{
		position.x += speed;
		if (GetAsyncKeyState(0x57))
		{
			position.y += speed;
			SetPosition(position);
			return position.x, position.y;
		}
		if (GetAsyncKeyState(0x53))
		{
			position.y -= speed;
			SetPosition(position);
			return position.x, position.y;
		}
		else
		{
			SetPosition(position);
			return position.x;
		}
	}

	if (GetAsyncKeyState(0x41))
	{
		position.x -= speed;
		if (GetAsyncKeyState(0x57))
		{
			position.y += speed;
			SetPosition(position);
			return position.x, position.y;
		}
		if (GetAsyncKeyState(0x53))
		{
			position.y -= speed;
			SetPosition(position);
			return position.x, position.y;
		}
		else
		{
			SetPosition(position);
			return position.x;
		}
	}



	if (GetAsyncKeyState(0x57))
	{
		position.y += speed;
		SetPosition(position);
		return position.y;
	}
	if (GetAsyncKeyState(0x53))
	{
		position.y -= speed;
		SetPosition(position);
		return position.y;
	}

}


void CPlayer::Update(float deltaTime)
{
	timeElapsed += deltaTime;

	const uint32_t speed = 24;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, (int(round(timeElapsed * speed) / 5) % 2) * 128));

	Movement(deltaTime);
}

CPlayer::~CPlayer()
{
	Debug::Log("destroy player class!\n");
}