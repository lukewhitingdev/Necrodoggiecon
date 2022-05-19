#include "CAnimationSpriteComponent.h"

CAnimationSpriteComponent::CAnimationSpriteComponent()
{
	SetShouldUpdate(true);
}

void CAnimationSpriteComponent::Update(float deltaTime)
{
	if (playing)
	{
		timeElapsed += deltaTime;

		float overspill = (timeElapsed * animSpeed - (animationRectSize.x * animationRectSize.y)) / animSpeed;
		if (overspill > 0.0f)
			timeElapsed = overspill;

		float animTime = timeElapsed * animSpeed;

		currentFrame = XMUINT2(int(floor(animTime)) % animationRectSize.x, (int(floor(animTime / animationRectSize.x))) % animationRectSize.y);

		SetTextureOffset(XMFLOAT2(CSpriteComponent::GetRenderRect().x * (animationRectPosition.x + currentFrame.x), 
									CSpriteComponent::GetRenderRect().y * (animationRectPosition.y + currentFrame.y)));
	}
}
