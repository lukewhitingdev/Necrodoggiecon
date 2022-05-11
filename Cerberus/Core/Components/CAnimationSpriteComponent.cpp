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

		/*SetTextureOffset(XMFLOAT2(round(timeElapsed * animSpeed) * CSpriteComponent::GetRenderRect().x,
			float((int(round(timeElapsed * animSpeed) / numberOfAnimationSprites.x) % numberOfAnimationSprites.y)) * CSpriteComponent::GetRenderRect().y));*/

		float animTime = timeElapsed * animSpeed;

		if (animTime > animationRectSize.x * animationRectSize.y)
		{
			timeElapsed = 0;
			animTime = timeElapsed * animSpeed;
		}

		currentFrame = XMUINT2(int(floor(animTime)) % animationRectSize.x, (int(floor(animTime)) * animationRectSize.x) % animationRectSize.y);

		SetTextureOffset(XMFLOAT2(CSpriteComponent::GetRenderRect().x * (animationRectPosition.x + currentFrame.x), 
									CSpriteComponent::GetRenderRect().y * (animationRectPosition.y + currentFrame.y)));
	}
}
