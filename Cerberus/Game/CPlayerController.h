#pragma once
#include <Cerberus\Core\CEntity.h>

class CCharacter;

class CPlayerController : public CEntity
{
private:
	CCharacter* possessedCharacter = nullptr;
	bool hasCharacter = false;

protected:
	CCharacter* GetCharacter() { return possessedCharacter; }
	bool HasCharacter() { return hasCharacter; }

	virtual void HandleInput(float deltaTime);

	virtual void OnPossess() {};
	virtual void OnUnpossess() {};

public:
	CPlayerController();
	~CPlayerController();

	void Possess(CCharacter* characterToPossess);
	void Unpossess();


};

