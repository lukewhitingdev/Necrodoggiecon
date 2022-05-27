#pragma once
#include "Cerberus\Core\CEntity.h"

class CursorEntity : public CEntity
{
	class CAnimationSpriteComponent* sprite = nullptr;

	Vector3 mouseOffset = { 0,0,0 };
	bool mouseLHeld = false;
	float zoomLevel = 0.0f;
	
public:
	CursorEntity();
	virtual void Update(float deltaTime) override;
	virtual ~CursorEntity();
};

