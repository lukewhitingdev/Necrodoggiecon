#pragma once

#include <string>
#include "Tile.h"
#include "Navigation.h"


class World
{

	World();

	World(int WorldSlot);

	void Load(int Slot);

	void Unload();

	//A List of all tiles in the scene
	//std::vector<Tile*> tileList;

	


};

