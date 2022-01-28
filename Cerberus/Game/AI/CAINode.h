#pragma once
#include "Environment/CWorld.h"

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