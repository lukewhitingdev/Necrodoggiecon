/*****************************************************************//**
 * \file   CInteractable.cpp
 * \brief  Entity that can be interacted with. Acts as a base class for any entities that wish to be interacted with in specfic ways.
 * 
 * \author Luke Whiting
 * \date   May 2022
 *********************************************************************/

#include "CInteractable.h"
#include "Cerberus\Core\Utility\DebugOutput\Debug.h"
#include "Cerberus\Core\Utility\InputManager\InputManager.h"

CInteractable::CInteractable() : interactTextOffset(0), interactRange(1), sprite(nullptr), lastCollidedObject(nullptr)
{
	sprite = AddComponent<CSpriteComponent>();
	interactText = AddComponent<CTextRenderComponent>();
	colComponent = new CollisionComponent("Interactable", this);

	colComponent->SetCollider(interactRange);
	colComponent->SetTrigger(true);
	sprite->LoadTexture("Resources/arrow.dds");

	interactText->SetScale(2, 2, 2);
}

CInteractable::~CInteractable()
{
	RemoveComponent(sprite);
	delete colComponent;
	colComponent = nullptr;
}

/**
 * Updates the interactables collision component and UI from showing / hiding when within range.
 * 
 * \param deltaTime
 */
void CInteractable::Update(float deltaTime)
{
	colComponent->SetPosition(this->GetPosition());

	Vector3 pos = this->GetPosition();
	
	if(lastCollidedObject != nullptr)
	{
		if (pos.DistanceTo(lastCollidedObject->GetPosition()) > interactRange)
		{
			OnLeaveOverlap();
		}
	}
}

/**
 * Called when a player has interacted with the interactable.
 * 
 */
void CInteractable::OnInteract()
{
	
	Debug::Log("Interact");
	Engine::DestroyEntity(this);
}

/**
 * Called when a player is withing range of the interactable.
 * 
 */
void CInteractable::OnEnterOverlap()
{
	DrawUI();
}

/**
 * Called when a player leaves the range of the interactable.
 * 
 */
void CInteractable::OnLeaveOverlap()
{
	interactText->SetText("");
}

/**
 * Called when a player is colliding with the trigger for the interactable.
 * 
 * \param collidedObject
 */
void CInteractable::HasCollided(CollisionComponent* collidedObject)
{
	lastCollidedObject = collidedObject;
	OnEnterOverlap();
	if(Inputs::InputManager::IsKeyPressedDown(Inputs::InputManager::F))
	{
		OnInteract();
	}
}

void CInteractable::SetTexture(std::string path)
{
	if (!sprite)
		sprite = AddComponent<CSpriteComponent>();

	sprite->LoadTexture(path);
}

void CInteractable::SetTextureWIC(std::string path)
{
	if (!sprite)
		sprite = AddComponent<CSpriteComponent>();

	sprite->LoadTextureWIC(path);
}

/**
 * Draws the UI to indicate which key to press to interact with the interactable.
 * 
 */
void CInteractable::DrawUI()
{
	interactText->SetPosition(Vector3(0, interactTextOffset, -3));
	interactText->SetText("F");
}
