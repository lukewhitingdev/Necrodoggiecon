#pragma once
#include "Cerberus\Core\CEntity.h"
#include "Cerberus/Core/Components/CCameraComponent.h"

class CursorEntity : public CEntity
{
	class CSpriteComponent* sprite = nullptr;
	class CTextRenderComponent* text = nullptr;
	float timeElapsed = 0;

	Vector3 mouseOffset = { 0,0,0 };
	bool mouseRHeld = false;
	
	CCameraComponent* camera;
public:
	CursorEntity();
	virtual void Update(float deltaTime) override;
	virtual ~CursorEntity();

	void SetCamera(CCameraComponent* cam);
};

