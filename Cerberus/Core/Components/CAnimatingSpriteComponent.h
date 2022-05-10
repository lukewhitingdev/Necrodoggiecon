/*****************************************************************//**
 * \file   CAnimatingSpriteComponent.h
 * \brief  Extends CSpriteComponent to automatically animate basic sprite sheets.
 * 
 * This class will automatically animate an entire sprite-sheet.
 * However, this animation is strictly the entire sprite-sheet only.
 * If you want more fine control, the methods for doing this manually is part of CSpriteComponent. 
 * 
 * \author Arrien Bidmead
 * \date   May 2022
 *********************************************************************/

#pragma once
#include "CSpriteComponent.h"

/**
 * Extends CSpriteComponent to automatically animate basic sprite sheets.
 */
class CAnimatingSpriteComponent : public CSpriteComponent
{
	float timeElapsed = 0.0f;
	uint32_t animSpeed = 24;
	XMUINT2 numberOfAnimationSprites = { 1, 1 };
	bool playing = true;

	/**
	 * Sets the number of sprites within the spritesheet.
	 */
	void SetNumberOfAnimationSprites() { numberOfAnimationSprites = XMUINT2(GetTextureSize().x / GetRenderRect().x, GetTextureSize().y / GetRenderRect().y); };

public:
	/**
	 * Set if the animation should be playing.
	 */
	void SetPlaying(const bool& newState) { playing = newState; };
	const bool& GetPlaying() { return playing; };

	/**
	 * Set the current animation time in the form of elapsed time.
	 * Note: this does NOT reset when the animation has finished.
	 */
	void SetElapsedTime(const float& newTime) { timeElapsed = newTime; };
	const float& GetElapsedTime() { return timeElapsed; };

	/**
	 * Sets the speed of the animation in frames per second - Default 24.
	 */
	void SetAnimationSpeed(const uint32_t& newSpeed) { animSpeed = newSpeed; };
	const uint32_t& GetAnimationSpeed() { return animSpeed; };

	/**
	 * Gets the auto-generated number of sprites in each dimension of the sprite-sheet.
	 * For instance, if the texture has 5 images in a row and 2 rows of images then it would be {5,2}
	 */
	const XMUINT2& GetNumberOfAnimationSprites() { return numberOfAnimationSprites; };

	/**
	 * Used to resize the portion of the texture you want to display on the sprite in pixels.
	 * Use to set the size of a selection of a sprite sheet.
	 */
	virtual void SetRenderRect(XMUINT2 newSize) override { CSpriteComponent::SetRenderRect(newSize); SetNumberOfAnimationSprites(); };

	/**
	 * The size of the ingame sprite in pixels.
	 * Set automatically on texture load.
	 */
	virtual void SetSpriteSize(XMUINT2 newSize) override { CSpriteComponent::SetSpriteSize(newSize); SetNumberOfAnimationSprites(); };

	CAnimatingSpriteComponent();
	virtual void Update(float deltaTime) override;
};
