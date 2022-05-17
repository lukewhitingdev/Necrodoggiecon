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

	virtual void HasCollided(CollisionComponent* collidedObject) override;

	void SetTexture(std::string path);
	void SetTextureWIC(std::string path);

	void SetInteractRange(const float value);

protected:
	void DrawUI();
	CollisionComponent* GetLastCollidedObject();

private:
	float interactTextOffset;
	float interactRange;
	CollisionComponent* lastCollidedObject;

	CSpriteComponent* sprite;
	CTextRenderComponent* interactText;

};

