#pragma once
#include <Necrodoggiecon\Game\CCharacter.h>
#include <Cerberus\Core\Environment\IInputable.h>

class CDroppedItem;
class CEquippedItem;

class PlayerCharacter : public CCharacter, public IInputable
{
protected:
	float speed = 200;
	float timeElapsed = 0;

	void LookAt(Vector3 pos);
public:
	PlayerCharacter();

	void SetCamera(class CCameraComponent* cam);

	void PressedHorizontal(int dir, float deltaTime) override;
	void PressedVertical(int dir, float deltaTime) override;
	void PressedInteract() override;
	void PressedDrop() override;
	virtual void Update(float deltaTime) override;

	virtual void HasCollided(CollisionComponent* collidedObject) override;

	CDroppedItem* droppedItem = nullptr;
	CEquippedItem* equippedItem = nullptr;
	class CCameraComponent* camera = nullptr;
};

