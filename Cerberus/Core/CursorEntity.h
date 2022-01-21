#pragma once
#include "CEntity.h"

class CursorEntity : public CEntity
{
	class CSpriteComponent* sprite = nullptr;
	class CTextRenderComponent* text = nullptr;
	float timeElapsed = 0;
public:
	CursorEntity();
	virtual void Update(float deltaTime) override;
	virtual ~CursorEntity();
};

