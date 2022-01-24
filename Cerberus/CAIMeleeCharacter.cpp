#include "CAIMeleeCharacter.h"

void CAIMeleeCharacter::GetIntoCover(CPlayer* player)
{
	Vector3 vectorToPlayer = aiPosition - player->GetPosition();
	Vector3 directionToPlayer = vectorToPlayer.Normalize();

}
