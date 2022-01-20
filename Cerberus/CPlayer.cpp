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

// simple movement for a player
Vector3 CPlayer::Movement(float deltaTime)
{
	float move = 200.0f;
	float speed = move * deltaTime;

	Vector3 myPos = GetPosition();

	if (GetAsyncKeyState(0x44))
	{
		myPos.x -= speed;
		if (GetAsyncKeyState(0x57))
		{
			myPos.y += speed;
			SetPosition(myPos);
			return myPos.x, myPos.y;
		}
		if (GetAsyncKeyState(0x53))
		{
			myPos.y -= speed;
			SetPosition(myPos);
			return myPos.x, myPos.y;
		}
		else
		{
			SetPosition(myPos);
			return myPos.x;
		}
	}

	if (GetAsyncKeyState(0x41))
	{
		myPos.x += speed;
		if (GetAsyncKeyState(0x57))
		{
			myPos.y += speed;
			SetPosition(myPos);
			return myPos.x, myPos.y;
		}
		if (GetAsyncKeyState(0x53))
		{
			myPos.y -= speed;
			SetPosition(myPos);
			return myPos.x, myPos.y;
		}
		else
		{
			SetPosition(myPos);
			return myPos.x;
		}
	}



	if (GetAsyncKeyState(0x57))
	{
		myPos.y += speed;
		SetPosition(myPos);
		return myPos.y;
	}
	if (GetAsyncKeyState(0x53))
	{
		myPos.y -= speed;
		SetPosition(myPos);
		return myPos.y;
	}

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