#include "CPickupItem.h"
/*****************************************************************//**
 * \file   CPickupItem.cpp
 * \brief  Class used for Pickup items, inherits from CEquippedItem
 *
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/
/**  
* Inherited function used to update the EquippedItem if necessary
*/
void CPickupItem::Update(float deltaTime)
{
	auto ownerPos = GetOwner()->GetPosition();
	ownerPos.y += 25;
	SetPosition(ownerPos);
}
/**
* Inherited function used to initialise the PickupItem
* Calls the base Initialise function
*/
void CPickupItem::Initialise(int id, CEntity* owner)
{
	CEquippedItem::Initialise(id, owner);
}
