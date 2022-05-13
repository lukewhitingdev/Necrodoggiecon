#include "MeleeEnemy.h"

MeleeEnemy::MeleeEnemy()
{
	
}

void MeleeEnemy::Update(float deltaTime)
{
	// Set the local variable for the AI position.
	aiPosition = GetPosition();

	// Run the finite state machine
	currentState->Update(this);

	CheckForPlayer();

	MoveViewFrustrum();

	// If the AI is not pathfinding or searching then check for collisions with obstacles.
	if (currentState != &PatrolState::getInstance() && currentState != &SearchState::getInstance())
		heading += CollisionAvoidance();

	// Move the AI if it is not lost
	if (currentState != &SearchState::getInstance())
		Movement(deltaTime);

	// Make sure the AI is on a 2D vector.
	aiPosition.z = 0.0f;

	// Set the position of the entity to the local variable for the AI position.
	SetPosition(aiPosition);
}
