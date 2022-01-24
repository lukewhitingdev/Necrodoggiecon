#pragma once
#include "CEntity.h"
#include "Vector3.h"
#include "CSpriteComponent.h"
#include "CAICharacter.h"
#include <iostream>
#include "CPlayer.h"
#include "Core/testClass.h"
#include "Utility/EventSystem/EventSystem.h"
#include "CWorld.h"
#include "CAINode.h"

enum class STATE
{
	PATROL,
	PATHFINDING,
	CHASE,
	ATTACK,
	COVER
};


class CAIController : public CEntity
{
public:
	CAIController();

protected:
	class CSpriteComponent* sprite = nullptr;

	virtual void Update(float deltaTime) override;

	void Movement(float deltaTime);

	bool CanSee(Vector3 position);

	STATE currentState;

	//BehaviourTree behaviourTree;

	Vector3 velocity;
	Vector3 acceleration;
	Vector3 heading;
	Vector3 aiPosition;

	std::vector<CTile*> tiles;
	std::vector<CTile*> obstacles;

	std::vector<PatrolNode*> patrolNodes;
	std::vector<WaypointNode*> waypointNodes;
	void SetPatrolNodes(std::vector<PatrolNode*> nodes, std::vector<CTile*> waypoints);
	PatrolNode* currentPatrolNode;

	PatrolNode* FindClosestPatrolNode();

	void StateMachine();
	void Patrolling();
	virtual void ChasePlayer(CPlayer* player);
	virtual void AttackPlayer(CPlayer* player);
	virtual void GetIntoCover(CPlayer* player);

	Vector3 Seek(Vector3 TargetPos);

	void SetPath(WaypointNode* goalWaypoint);
	void CalculatePath(WaypointNode* start, WaypointNode* goal);
	float CalculateCost(WaypointNode* from, WaypointNode* to);
	void ResetNodes();
	void DeleteNodes();
	
	std::vector<WaypointNode*> open;
	std::vector<WaypointNode*> closed;

	// Array of nodes on the path from goal to start.
	std::vector<WaypointNode*> pathNodes;
	int currentCount;

	CPlayer* playerToKill = nullptr;
	CPlayer* playerToChase = nullptr;
	std::vector<CPlayer*> players = Engine::GetEntityOfType<CPlayer>();
	CAICharacter* viewFrustrum = Engine::CreateEntity<CAICharacter>();
	class CSpriteComponent* viewSprite = nullptr;

	int aiHealth = 2;
	float aiSpeed = 100.0f;
	float aiMass = 10.0f;
	float aiRange = 400.0f;
	float aiViewAngle = 45.0f;

	void SetHealth(int health);
	int GetHealth();
	void SetSpeed(int speed);
	int GetSpeed();
	void SetMass(int mass);
	int GetMass(); 
	void SetRange(int range);
	int GetRange();
	void SetViewAngle(int angle);
	int GetViewAngle();
};

