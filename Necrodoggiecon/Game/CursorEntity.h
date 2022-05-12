#pragma once
#include "Cerberus\Core\CEntity.h"

class CursorEntity : public CEntity
{
	class CAnimationSpriteComponent* sprite = nullptr;
	class CTextRenderComponent* text = nullptr;
	float timeElapsed = 0;

	Vector3 mouseOffset = { 0,0,0 };
	bool mouseRHeld = false;
public:
	CursorEntity();
	virtual void Update(float deltaTime) override;
	virtual ~CursorEntity();
};

