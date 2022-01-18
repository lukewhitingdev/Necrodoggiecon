#pragma once
#include "CComponent.h"
#include "Vector3.h"
#include <iostream>

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
};

class CAIController : public CComponent
{
	enum STATE
	{
		PATROL,
		PATHFINDING,
		CHASE,
		ATTACK,
		COVER
	};

protected:
	CAIController();

	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context) override;

	STATE currentState;

	//BehaviourTree behaviourTree;

	Vector3 velocity;
	Vector3 heading;

	void MoveInHeadingDirection(float deltaTime);

	std::vector<PatrolNode*> patrolNodes;
	std::vector<WaypointNode*> waypointNodes;
	void SetPatrolNodes(std::vector<PatrolNode*> nodes, std::vector<Waypoint*> waypoints);
	PatrolNode* currentPatrolNode;

	PatrolNode* FindClosestPatrolNode();
	
	float mass;
	float speed;

	void StateMachine(float deltaTime);
	void Patrolling();

	Vector3 Seek(Vector3 TargetPos);

	void SetPath();
	void CalculatePath(WaypointNode* start, WaypointNode* goal);
	float CalculateCost(float x, float y, float x2, float y2);
	void ResetNodes();
	void DeleteNodes();
	
	std::vector<WaypointNode*> open;
	std::vector<WaypointNode*> closed;
	std::vector<WaypointNode*> nodes;

	// Array of nodes on the path from goal to start.
	std::vector<WaypointNode*> pathNodes;
	int currentCount;
};

