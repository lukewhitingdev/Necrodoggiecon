#include "testClass.h"
#include "Utility/DebugOutput/Debug.h"
#include "../CSpriteComponent.h"
#include "Utility/CollisionManager/Components/Bodies/CollisionComponent.h"
#include "Utility/CollisionManager/Components/Bodies/BoundingSphere.h"

TestClass::TestClass()
{
	Debug::Log("init test class!\n");

	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\birb.dds");
	sprite->SetRenderRect(XMUINT2(128, 128));
	sprite->SetSpriteSize(XMUINT2(128, 128));

	sprite->SetTint(XMFLOAT4(float(rand() % 2 * .5), float(rand() % 2 * .5), float(rand() % 2 * .5), 0));

	//colComponent = AddComponent<CollisionComponent>();


	if (rand() % 2)
		sprite->SetScale(-1, 1, 1);

	timeElapsed = float(rand() / 100);
}

void TestClass::Update(float deltaTime)
{
	//CEntity::Update(deltaTime);

	timeElapsed += deltaTime;

	const uint32_t speed = 24;
	sprite->SetTextureOffset(XMFLOAT2(round(timeElapsed * speed) * 128, float((int(round(timeElapsed * speed) / 5) % 2)) * 128));

	/*float speed = 200.0f;
	float deltaSpeed = speed * deltaTime;

	Vector3 moveDir = { 0,0,0 };

	if (GetAsyncKeyState(0x44))
		moveDir += Vector3(1, 0, 0);
	if (GetAsyncKeyState(0x41))
		moveDir += Vector3(-1, 0, 0);
	if (GetAsyncKeyState(0x57))
		moveDir += Vector3(0, 1, 0);
	if (GetAsyncKeyState(0x53))
		moveDir += Vector3(0, -1, 0);

	if (moveDir.Magnitude() > 0.0f)
	{
		moveDir.normalize();
		SetPosition(GetPosition() + moveDir * deltaSpeed);
	}*/
}

TestClass::~TestClass()
{
	Debug::Log("destroy test class!\n");
}
