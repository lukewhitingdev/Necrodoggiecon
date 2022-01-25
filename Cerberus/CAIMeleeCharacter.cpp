#include "CAIMeleeCharacter.h"

void CAIMeleeCharacter::GetIntoCover(testCharacter* player)
{
	Vector3 vectorToPlayer = aiPosition - player->GetPosition();
	Vector3 directionToPlayer = vectorToPlayer.Normalize();

}
