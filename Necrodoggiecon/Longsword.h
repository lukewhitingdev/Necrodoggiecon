/*****************************************************************//**
 * \file   Longsword.h
 * \brief  Sub-Class for the Longsword weapon. This will include all unique logic for the weapon (AOE Slashing)
 * 
 * \author Ben Brown
 * \date   May 2022
 *********************************************************************/

#pragma once
#include <Necrodoggiecon\Game\weapons.h>

class Longsword : public Weapon
{
public:
	Longsword();
	~Longsword();

	virtual void OnFire(Vector3 actorPos, Vector3 attackDir);
private:
	//std::vector<CEntity*> GetPlayersInReach(Vector3 actorPos, Vector3 damagePos);
};

