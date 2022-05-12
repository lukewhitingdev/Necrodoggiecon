/*****************************************************************//**
 * \file   State.cpp
 * \brief  Functions for all the functions for the states.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#include "State.h"
#include "CAIController.h"

void ChaseState::Enter(CAIController* controller)
{
	Vector3 aiPosition = controller->GetPosition();
	std::vector<PlayerCharacter*> players = Engine::GetEntityOfType<PlayerCharacter>();

	for (PlayerCharacter* player : players)
	{
		// Find if the player is the closest in view.
		if (controller->CanSee(player->GetPosition()) == true)
		{
			if (closestPlayer != nullptr)
			{
				if (aiPosition.DistanceTo(player->GetPosition()) < aiPosition.DistanceTo(closestPlayer->GetPosition()))
				{
					closestPlayer = player;
				}
			}
			else
			{
				closestPlayer = player;
			}
		}
	}
}

void ChaseState::Update(CAIController* controller)
{
	if (controller->CanSee(closestPlayer->GetPosition()) == true)
	{
		controller->ChasePlayer(closestPlayer);
	}
	else
	{
		controller->SetCurrentState(SearchState::getInstance());
	}
}

void ChaseState::Exit(CAIController* controller)
{
}

State& ChaseState::getInstance()
{
	static ChaseState singleton;
	return singleton;
}

void AttackState::Enter(CAIController* controller)
{
	Vector3 aiPosition = controller->GetPosition();
	std::vector<PlayerCharacter*> players = Engine::GetEntityOfType<PlayerCharacter>();

	for (PlayerCharacter* player : players)
	{
		// Find if the player is the closest in view.
		if (closestPlayer != nullptr)
		{
			if (aiPosition.DistanceTo(player->GetPosition()) < aiPosition.DistanceTo(closestPlayer->GetPosition()))
			{
				closestPlayer = player;
			}
		}
		else
		{
			closestPlayer = player;
		}
	}
}

void AttackState::Update(CAIController* controller)
{
	if (closestPlayer != nullptr)
	{
		controller->AttackPlayer(closestPlayer);
		closestPlayer = nullptr;
	}
	else
	{
		controller->SetCurrentState(PatrolState::getInstance());
	}
}

void AttackState::Exit(CAIController* controller)
{
}

State& AttackState::getInstance()
{
	static AttackState singleton;
	return singleton;
}

void PatrolState::Enter(CAIController* controller)
{
	controller->SetPath();
}

void PatrolState::Update(CAIController* controller)
{
	controller->Patrolling();
}

void PatrolState::Exit(CAIController* controller)
{
}

State& PatrolState::getInstance()
{
	static PatrolState singleton;
	return singleton;
}

void SearchState::Enter(CAIController* controller)
{
	searchTimer = 5.0f;
	players = Engine::GetEntityOfType<PlayerCharacter>();
}

void SearchState::Update(CAIController* controller)
{
	if (searchTimer > 0.0f)
	{
		searchTimer -= 0.016f;

		for (PlayerCharacter* player : players)
		{
			if (controller->CanSee(player->GetPosition()) == true)
			{
				controller->SetCurrentState(ChaseState::getInstance());
			}
		}
		
		controller->SearchForPlayer();

		// If the timer is up then go back to pathfinding.
		if (searchTimer < 0.02f)
			controller->SetCurrentState(PatrolState::getInstance());
	}
}

void SearchState::Exit(CAIController* controller)
{
}

State& SearchState::getInstance()
{
	static SearchState singleton;
	return singleton;
}
