#pragma once
/*****************************************************************//**
 * \file   State.h
 * \brief  Header files containing the base state class and any inheritted states for the FSM of the AI.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#include "Necrodoggiecon/Game/PlayerCharacter.h"
class CAIController;

//Reference: https://www.aleksandrhovhannisyan.com/blog/finite-state-machine-fsm-tutorial-implementing-an-fsm-in-c/

/**
 * Base state class.
 */
class State
{
public:

	virtual void Enter(CAIController* controller) { UNREFERENCED_PARAMETER(controller); };
	virtual void Exit(CAIController* controller) { UNREFERENCED_PARAMETER(controller); };
	virtual void Update(CAIController* controller, float deltaTime) { UNREFERENCED_PARAMETER(controller); UNREFERENCED_PARAMETER(deltaTime); };
	
};

/**
 * State for when the AI is chasing the player.
 */
class ChaseState : public State
{
public:
	void Enter(CAIController* controller) override;
	void Update(CAIController* controller, float deltaTime) override;
	void Exit(CAIController* controller) override;

	static State& getInstance();

private:
	PlayerCharacter* closestPlayer;
};

/**
 * State for when the AI is attacking the player.
 */
class AttackState : public State
{
public:
	void Enter(CAIController* controller) override;
	void Update(CAIController* controller, float deltaTime) override;
	void Exit(CAIController* controller) override;

	static State& getInstance();

private:
	PlayerCharacter* closestPlayer;
};

/**
 * State for when the AI is patrolling between the patrol points.
 */
class PatrolState : public State
{
public:
	void Enter(CAIController* controller) override;
	void Update(CAIController* controller, float deltaTime) override;
	void Exit(CAIController* controller) override;

	static State& getInstance();
};

/**
 * State for when the AI is searching for the player. The AI will spin on the spot looking for the player.
 */
class SearchState : public State
{
public:
	void Enter(CAIController* controller) override;
	void Update(CAIController* controller, float deltaTime) override;
	void Exit(CAIController* controller) override;

	static State& getInstance();

private:
	float searchTimer;
	std::vector<PlayerCharacter*> players;
};

/**
 * State for when the AI is investigating. The AI will path to the ivestigation position then enter the search state.
 */
class InvestigateState : public State
{
public:
	void Enter(CAIController* controller) override;
	void Update(CAIController* controller, float deltaTime) override;
	void Exit(CAIController* controller) override;

	static State& getInstance();

private:

};
