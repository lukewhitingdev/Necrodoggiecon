#include "CAICharacter.h"

CAICharacter::CAICharacter()
{
	viewSprite = AddComponent<CSpriteComponent>();
	viewSprite->LoadTexture("Resources/arrow.dds");
	viewSprite->SetTint(XMFLOAT4(0.0f, 0.0f, 0.0f, 0));
	viewSprite->SetScale(Vector3{ 0.01f, 0.01f, 0.01f });

}

void CAICharacter::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

CAICharacter::~CAICharacter()
{
}
