#include "CInteractable.h"
#include "Cerberus\Core\Utility\DebugOutput\Debug.h"
#include "Cerberus\Core\Utility\InputManager\InputManager.h"

CInteractable::CInteractable() : interactTextOffset(0), interactRange(1), sprite(nullptr), lastCollidedObject(nullptr)
{
	sprite = AddComponent<CSpriteComponent>(NAME_OF(sprite));
	interactText = AddComponent<CTextRenderComponent>(NAME_OF(interactText));
	colComponent = new CollisionComponent("Interactable", this);

	sprite->LoadTexture("Resources/Game/arrow.dds");
	this->SetInteractRange(sprite->GetSpriteSize().x);

	colComponent->SetCollider(interactRange);
	colComponent->SetTrigger(true);

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
 * \param collidedObject the other object we are colliding with.
 */
void CInteractable::HasCollided(CollisionComponent* collidedObject)
{
	static bool keyPressed;

	lastCollidedObject = collidedObject;
	OnEnterOverlap();
	if(InputManager::IsKeyPressedDown(InputManager::F) && !keyPressed)
	{
		OnInteract();
		keyPressed = true;
	}

	if(InputManager::IsKeyReleased(InputManager::F))
		keyPressed = false;

}

/**
 * Sets the texture for the interactable.
 * 
 * \param path the path to the texture used for the interactable.
 */
void CInteractable::SetTexture(std::string path)
{
	if (!sprite)
		sprite = AddComponent<CSpriteComponent>(NAME_OF(sprite));

	sprite->LoadTexture(path);
}

/**
 * Sets the texture for the interactable.
 * 
 * \param path the path to the texture used for the interactable.
 */
void CInteractable::SetTextureWIC(std::string path)
{
	if (!sprite)
		sprite = AddComponent<CSpriteComponent>(NAME_OF(sprite));

	sprite->LoadTextureWIC(path);
}

/**
 * Sets the interact range for the interactable.
 * 
 * \param value the interact range for the interactable.
 */
void CInteractable::SetInteractRange(const float value)
{
	interactRange = value;
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

/**
 * Returns the last collided object of the interactable.
 * 
 * \return the collision component pointer of the last collided object.
 */
CollisionComponent* CInteractable::GetLastCollidedObject()
{
	return lastCollidedObject;
}

/**
 * Returns the sprite of the interactable.
 * 
 * \return the sprite of the interactable.
 */
CSpriteComponent* CInteractable::GetSprite()
{
	return sprite;
}
