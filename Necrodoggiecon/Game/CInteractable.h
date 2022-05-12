#pragma once
#include "Cerberus\Core\CEntity.h"
#include "Cerberus\Core\Components\CSpriteComponent.h"
#include "Cerberus\Core\Components\CTextRenderComponent.h"
class CInteractable : public CEntity
{
public:
	CInteractable();
	virtual ~CInteractable();

	void Update(float deltaTime);

	virtual void OnInteract();
	virtual void OnEnterOverlap();
	virtual void OnLeaveOverlap();

	virtual void HasCollided(CollisionComponent* collidedObject);

protected:
	void DrawUI();

private:
	float interactTextOffset;
	float interactRange;

	CSpriteComponent* sprite;
	CTextRenderComponent* interactText;

	CollisionComponent* lastCollidedObject;
};

