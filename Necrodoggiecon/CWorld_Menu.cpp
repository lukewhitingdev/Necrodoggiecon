/*******************************************************************
 * \file   CWorld_Menu.cpp
 * \brief  
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#include "CWorld_Menu.h"
#include "Cerberus/Core/Utility/CUIManager.h"
#include "Necrodoggiecon/MainMenu.h"
#include "Cerberus/Core/Components/CCameraComponent.h"
#include "Cerberus/Core/Structs/CCamera.h"
#include "Cerberus/Core/Utility/CameraManager/CameraManager.h"
#include "Game/SoundManager.h"


/**
 * Sets up the world, in this case, loads the main menu canvas.
 * 
 */
void CWorld_Menu::SetupWorld()
{
	SoundManager::Initialise();

	// Free Camera not locked to player.
	CCamera* freeCamera = Engine::CreateEntity<CCamera>();
	CCameraComponent* freeCameraComponent = freeCamera->AddComponent<CCameraComponent>(NAME_OF(freeCameraComponent));
	freeCameraComponent->SetAttachedToParent(false);
	CameraManager::SetRenderingCamera(freeCameraComponent);

	CUIManager::AddCanvas(Engine::CreateEntity<MainMenu>(), "MainMenu");
	SoundManager::PlayMusic("Resources/Game/Audio/MenuBGM.wav", nullptr);
}
