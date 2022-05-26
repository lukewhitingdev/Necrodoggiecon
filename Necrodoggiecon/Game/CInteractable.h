/*****************************************************************//**
 * \file   CInteractable.h
 * \brief  Entity that can be interacted with. Acts as a base class for any entities that wish to be interacted with in specfic ways.
 *
 * \author Luke Whiting
 * \date   May 2022
 *********************************************************************/
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
	CSpriteComponent* GetSprite();

private:
	float interactTextOffset;
	float interactRange;
	CollisionComponent* lastCollidedObject;

	CSpriteComponent* sprite;
	CTextRenderComponent* interactText;

};

