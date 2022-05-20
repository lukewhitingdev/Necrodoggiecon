/*******************************************************************
 * \file   CWorld_Game.cpp
 * \brief  Child class of CWorld created for the game, overrides world setup from parent.
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "CWorld_Game.h"
#include <Necrodoggiecon\Game\PlayerController.h>
#include <Necrodoggiecon\Game\PlayerCharacter.h>
#include <Cerberus\Core\Components\CCameraComponent.h>
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include <Cerberus/Core/Structs/CCamera.h>



/**
 * Constructor, automatically loads world based on provided slot.
 * 
 * \param Slot
 * Determines which level to load.
 */
CWorld_Game::CWorld_Game(int Slot)
{
	LoadWorld(Slot);
}

/**  */
void CWorld_Game::SetupWorld()
{
	PlayerController* controller = Engine::CreateEntity<PlayerController>();
	PlayerCharacter* character1 = Engine::CreateEntity<PlayerCharacter>();

	controller->charOne = character1;
	
	Vector3 PlayerStart = Vector3(StartPos.x, StartPos.y, 0) * (tileScale * tileScaleMultiplier) + Vector3(0, 0, -1);
	Debug::Log("Player Start Position: [%f | %f]", PlayerStart.x, PlayerStart.y);
	character1->SetPosition(PlayerStart);
	controller->Possess(character1);
	character1->SetShouldMove(true);
	character1->colComponent->SetCollider(128.0f, 128.0f);

}
