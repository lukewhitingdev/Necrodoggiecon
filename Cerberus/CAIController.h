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

const float speed = 200.0f;
const float mass = 100.0f;
const float viewRange = 400.0f;

struct Waypoint
{
	Vector3 position;
	int waypointID;
	std::vector<int> connectedIDs;

	Waypoint(int id, Vector3 pos, std::vector<int> connected) : waypointID(id), position(pos), connectedIDs(connected) {}

	// Returns the position of the waypoint.
	Vector3 GetPosition()
	{
		return position;
	}

	// Returns the ID of the waypoint.
	int GetID()
	{
		return waypointID;
	}

	// Returns a vector array of neighbour IDs.
	std::vector<int> GetConnectedWaypointIDs()
	{
		return connectedIDs;
	}
};

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

	int tileSize;
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
	float CalculateCost(float x, float y, float x2, float y2);
	void ResetNodes();
	void DeleteNodes();
	
	std::vector<WaypointNode*> open;
	std::vector<WaypointNode*> closed;

	// Array of nodes on the path from goal to start.
	std::vector<WaypointNode*> pathNodes;
	int currentCount;

	CPlayer* player = Engine::CreateEntity<CPlayer>();
	CAICharacter* viewFrustrum = Engine::CreateEntity<CAICharacter>();
	class CSpriteComponent* viewSprite = nullptr;
};

