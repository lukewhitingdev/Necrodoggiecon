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
}

void CPickupItem::OnInteract()
{
	switch (pickupType)
	{
	case PickupType::INVISIBILITY_SCROLL:
		break;
	case PickupType::SHIELD_SCROLL:
		break;
	case PickupType::NECRODOGGICON_PAGE:
		break;
	default:
		break;
	}
}
