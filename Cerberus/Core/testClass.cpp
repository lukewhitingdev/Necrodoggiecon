#include "testClass.h"
#include "Utility/DebugOutput/Debug.h"
#include "../CTextRenderComponent.h"

TestClass::TestClass()
{
	Debug::Log("init test class!\n");

	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\birb.dds");
	sprite->SetRenderRect(XMUINT2(128, 128));
	sprite->SetSpriteSize(XMUINT2(128, 128));
	sprite->SetPosition(0, 128, 0);

	text = AddComponent<CTextRenderComponent>();
	text->SetText("thisistext.");

	sprite->SetTint(XMFLOAT4(float(rand() % 2 * .5), float(rand() % 2 * .5), float(rand() % 2 * .5), 0));

	if (rand() % 2)
		sprite->SetScale(-1, 1, 1);

	timeElapsed = float(rand() / 100);
}

void TestClass::Update(float deltaTime)
{
	//CEntity::Update(deltaTime);

	timeElapsed += deltaTime;

	const uint32_t speed = 24;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, (int(round(timeElapsed * speed) / 5) % 2) * 128));

	float speed2;
	if (Input::GetKeyState(Keys::Shift))
		speed2 = 400.0f;
	else
		speed2 = 200.0f;

	float deltaSpeed = speed2 * deltaTime;

	Vector3 moveDir = { 0,0,0 };

	if (Input::GetKeyState(Keys::D))
		moveDir += Vector3(1, 0, 0);
	if (Input::GetKeyState(Keys::A))
		moveDir += Vector3(-1, 0, 0);
	if (Input::GetKeyState(Keys::W))
		moveDir += Vector3(0, 1, 0);
	if (Input::GetKeyState(Keys::S))
		moveDir += Vector3(0, -1, 0);

	if (moveDir.Magnitude() > 0.0f)
	{
		moveDir.normalize();
		SetPosition(GetPosition() + moveDir * deltaSpeed);
	}

	if (Input::GetKeyState(Keys::One))
		text->SetText("thisistext.");
	if (Input::GetKeyState(Keys::Two))
		text->SetText("ran");
	if (Input::GetKeyState(Keys::Three))
		text->SetText("kjbdgfkjsdbbsdfg");
}

TestClass::~TestClass()
{
	Debug::Log("destroy test class!\n");
}
