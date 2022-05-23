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

	controller->ChaseEnter();
}

void ChaseState::Update(CAIController* controller, float deltaTime)
{
	if (controller->CanSee(closestPlayer->GetPosition()) == true)
	{
		controller->ChasePlayer(closestPlayer);
	}
	else
	{
		controller->SetPositionToInvestigate(closestPlayer->GetPosition());
		controller->SetCurrentState(InvestigateState::getInstance());
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

	controller->AttackEnter(closestPlayer);
}

void AttackState::Update(CAIController* controller, float deltaTime)
{
	if (closestPlayer != nullptr)
	{
		controller->AttackPlayer(closestPlayer, deltaTime);
		if (controller->CanSee(closestPlayer->GetPosition()) == false && controller->GetIsAttacking() == false)
		{
			controller->SetPositionToInvestigate(closestPlayer->GetPosition());
			closestPlayer = nullptr;
			controller->SetCurrentState(InvestigateState::getInstance());
		}
	}
	else
	{
		controller->SetCurrentState(PatrolState::getInstance());
	}
}

void AttackState::Exit(CAIController* controller)
{
	controller->SetSpeed(controller->GetInititalSpeed());
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

void PatrolState::Update(CAIController* controller, float deltaTime)
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
	searchTimer = 10.0f;
	players = Engine::GetEntityOfType<PlayerCharacter>();
}

void SearchState::Update(CAIController* controller, float deltaTime)
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
	searchTimer = 10.0f;
}

State& SearchState::getInstance()
{
	static SearchState singleton;
	return singleton;
}

void InvestigateState::Enter(CAIController* controller)
{
	controller->SetPath(controller->GetPositionToInvestigate());
}

void InvestigateState::Update(CAIController* controller, float deltaTime)
{
	controller->Investigating(controller->GetPositionToInvestigate());
}

void InvestigateState::Exit(CAIController* controller)
{
}

State& InvestigateState::getInstance()
{
	static InvestigateState singleton;
	return singleton;
}
