#include "CAnimationSpriteComponent.h"

CAnimationSpriteComponent::CAnimationSpriteComponent()
{
	shouldUpdate = true;
}

void CAnimationSpriteComponent::Update(float deltaTime)
{
	if (playing)
	{
		timeElapsed += deltaTime;

		SetTextureOffset(XMFLOAT2(round(timeElapsed * animSpeed) * CSpriteComponent::GetRenderRect().x,
			float((int(round(timeElapsed * animSpeed) / numberOfAnimationSprites.x) % numberOfAnimationSprites.y)) * CSpriteComponent::GetRenderRect().y));
	}
}
