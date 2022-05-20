#include "CCharacter.h"
/*****************************************************************//**
 * \file   CCharacter.cpp
 * \brief  Base class for Characters
 *
 * \author Cathan Bertram
 * \date   May 2022
 *********************************************************************/
CCharacter::CCharacter()
{
}

CCharacter::~CCharacter()
{
}
/*
* Function to add vertical movement to the character
* dir is the direction on the y axis that the character will move
* speed is how fast to move the character
* deltaTime is used to ensure the character will move at a consistent speed that is not dependent on frame rate
*/
void CCharacter::AddVerticalMovement(int dir, float speed, float deltaTime)
{
	Vector3 pos = GetPosition();
	pos.y += dir * (speed * deltaTime);
	SetPosition(pos);
}
/**
* Function to add vertical movement to the character
* dir is the direction on the y axis that the character will move
* speed is how fast to move the character
* deltaTime is used to ensure the character will move at a consistent speed that is not dependent on frame rate
*/
void CCharacter::AddHorizontalMovement(int dir, float speed, float deltaTime)
{
	Vector3 pos = GetPosition();
	pos.x += dir * (speed * deltaTime);
	SetPosition(pos);
}
