/*****************************************************************//**
 * \file   CAnimationSpriteComponent.h
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
class CAnimationSpriteComponent : public CSpriteComponent
{
	float timeElapsed = 0.0f;
	uint32_t animSpeed = 24;
	bool playing = true;
	XMUINT2 animationRectSize = { 1,1 };
	XMUINT2 animationRectPosition = { 0,0 };
	XMUINT2 currentFrame = { 0,0 };	//relative to the animation rect.

public:
	void RestartAnimation() { timeElapsed = 0.0f; };

	/**
	 * Sets the size of the rectangle in sprites to which the animation is played within.
	 * Like narrowing down the sprite to just the animation you want.
	 */
	void SetAnimationRectSize(const XMUINT2& newSize) { animationRectSize = newSize; };
	const XMUINT2& GetAnimationRectSize() { return animationRectSize; };

	/**
	 * Sets the position of the rectangle in sprites to which the animation is played within.
	 * This is the point of the top left of the animation rect.
	 * Use this to select the portion of the sprite to display.
	 */
	void SetAnimationRectPosition(const XMUINT2& newPosition) { animationRectPosition = newPosition; };
	const XMUINT2& GetAnimationRectPosition() { return animationRectPosition; };

	const XMUINT2& GetCurrentFrame() { return currentFrame; };

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

	CAnimationSpriteComponent();
	virtual void Update(float deltaTime) override;
};
