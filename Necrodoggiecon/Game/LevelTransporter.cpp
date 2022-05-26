#include "LevelTransporter.h"
#include "Cerberus/Core/Utility/CWorldManager.h"

LevelTransporter::LevelTransporter()
{
}

void LevelTransporter::OnInteract()
{
	CWorldManager::LoadWorld(new CWorld_Game(Slot));
}
