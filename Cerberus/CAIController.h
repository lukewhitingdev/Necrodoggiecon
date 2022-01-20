#pragma once
#include "Engine.h"
#include "CEntity.h"
#include "Vector3.h"
#include "CSpriteComponent.h"
#include <iostream>

const float speed = 200.0f;
const float mass = 100.0f;

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
	Waypoint* waypoint;
	Waypoint* parentWaypoint;
	std::vector<WaypointNode*> neighbours;
	float gCost;
	float hCost;
	float fCost = gCost + hCost;
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

class CAIController : public CEntity
{
	enum STATE
	{
		PATROL,
		PATHFINDING,
		CHASE,
		ATTACK,
		COVER
	};

public:
	CAIController();

protected:
	class CSpriteComponent* sprite = nullptr;

	virtual void Update(float deltaTime) override;

	void Movement(float deltaTime);

	STATE currentState;

	//BehaviourTree behaviourTree;

	Vector3 velocity;
	Vector3 acceleration;
	Vector3 heading;

	std::vector<PatrolNode*> patrolNodes;
	std::vector<WaypointNode*> waypointNodes;
	void SetPatrolNodes(std::vector<PatrolNode*> nodes, std::vector<Waypoint*> waypoints);
	PatrolNode* currentPatrolNode;

	PatrolNode* FindClosestPatrolNode();

	void StateMachine();
	void Patrolling();

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
};

