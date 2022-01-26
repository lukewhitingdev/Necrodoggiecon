#include "CAICharacter.h"

CAICharacter::CAICharacter()
{
	viewSprite = AddComponent<CSpriteComponent>();
	viewSprite->LoadTexture("Resources\\viewFrustrum.dds");
	viewSprite->SetTint(XMFLOAT4(0.0f, 0.0f, 0.0f, 0));
	viewSprite->SetScale(Vector3{ 1.0f, 1.0f, 1.0f });
}

void CAICharacter::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

CAICharacter::~CAICharacter()
{
}
