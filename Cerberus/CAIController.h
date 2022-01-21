#pragma once
#include "Engine.h"
#include "CEntity.h"
#include "Vector3.h"
#include "CSpriteComponent.h"
#include "CAICharacter.h"
#include <iostream>
#include "CPlayer.h"
#include "Core/testClass.h"
#include "Utility/EventSystem/EventSystem.h"
#include "CWorld.h"



struct WaypointNode
{
	CTile* waypoint = nullptr;
	CTile* parentWaypoint = nullptr;
	std::vector<WaypointNode*> neighbours;
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
};

struct PatrolNode
{
	Vector3 position;
	WaypointNode* closestWaypoint;
	PatrolNode* nextPatrolNode;

	PatrolNode(Vector3 pos) : position(pos) 
	{
		closestWaypoint = nullptr;
		nextPatrolNode = nullptr;
	}
};

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

	bool CanSeePlayer();

	STATE currentState;

	//BehaviourTree behaviourTree;

	Vector3 velocity;
	Vector3 acceleration;
	Vector3 heading;
	Vector3 position;

	std::vector<CTile*> tiles;

	std::vector<PatrolNode*> patrolNodes;
	std::vector<WaypointNode*> waypointNodes;
	void SetPatrolNodes(std::vector<PatrolNode*> nodes, std::vector<CTile*> waypoints);
	PatrolNode* currentPatrolNode;

	PatrolNode* FindClosestPatrolNode();

	void StateMachine();
	void Patrolling();
	virtual void ChasePlayer();
	virtual void AttackPlayer();

	Vector3 Seek(Vector3 TargetPos);

	void SetPath();
	void CalculatePath(WaypointNode* start, WaypointNode* goal);
	float CalculateCost(WaypointNode* from, WaypointNode* to);
	void ResetNodes();
	void DeleteNodes();
	
	std::vector<WaypointNode*> open;
	std::vector<WaypointNode*> closed;

	// Array of nodes on the path from goal to start.
	std::vector<WaypointNode*> pathNodes;
	int currentCount;

	CPlayer* player = Engine::GetEntityOfType<CPlayer>()[0];
	CAICharacter* viewFrustrum = Engine::CreateEntity<CAICharacter>();
	class CSpriteComponent* viewSprite = nullptr;

	int aiHealth = 2;
	float aiSpeed = 200.0f;
	float aiMass = 100.0f;
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

