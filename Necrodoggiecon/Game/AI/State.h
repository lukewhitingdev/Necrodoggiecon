#pragma once
/*****************************************************************//**
 * \file   State.h
 * \brief  Header files containing the base state class and any inheritted states for the FSM of the AI.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#include "Necrodoggiecon/Game/testCharacter.h"
class CAIController;

//Reference: https://www.aleksandrhovhannisyan.com/blog/finite-state-machine-fsm-tutorial-implementing-an-fsm-in-c/

class State
{
public:

	virtual void Enter(CAIController* controller) {};
	virtual void Exit(CAIController* controller) {};
	virtual void Update(CAIController* controller) {};
	
};


class ChaseState : public State
{
public:
	void Enter(CAIController* controller) override;
	void Update(CAIController* controller) override;
	void Exit(CAIController* controller) override;

	static State& getInstance();

private:
	testCharacter* closestPlayer;
};

class AttackState : public State
{
public:
	void Enter(CAIController* controller) override;
	void Update(CAIController* controller) override;
	void Exit(CAIController* controller) override;

	static State& getInstance();

private:
	testCharacter* closestPlayer;
};

class PatrolState : public State
{
public:
	void Enter(CAIController* controller) override;
	void Update(CAIController* controller) override;
	void Exit(CAIController* controller) override;

	static State& getInstance();
};

class SearchState : public State
{
public:
	void Enter(CAIController* controller) override;
	void Update(CAIController* controller) override;
	void Exit(CAIController* controller) override;

	static State& getInstance();

private:
	float searchTimer;
	std::vector<testCharacter*> players;
};
