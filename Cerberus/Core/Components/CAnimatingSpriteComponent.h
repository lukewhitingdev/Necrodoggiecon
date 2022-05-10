/*****************************************************************//**
 * \file   CAnimatingSpriteComponent.h
 * \brief  Extends CSpriteComponent to automatically animate basic sprite sheets.
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
	 * Sets the speed of the animation in frames per second - Default 24.
	 */
	void SetAnimationSpeed(const uint32_t& newSpeed) { animSpeed = newSpeed; };
	const uint32_t& GetAnimationSpeed() { return animSpeed; };

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
