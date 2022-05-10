#pragma once
#include "CAINode.h"

class Pathfinding
{
public:
	Pathfinding(std::vector<CTile*> waypoints);
	
	void SetPatrolNodes(std::vector<PatrolNode*> nodes);
	WaypointNode* FindClosestWaypoint(Vector3 position);
	PatrolNode* FindClosestPatrolNode(Vector3 position);

	void SetPath(Vector3 currentPosition, WaypointNode* goalWaypoint);
	void CalculatePath(WaypointNode* start, WaypointNode* goal);
	float CalculateCost(WaypointNode* from, WaypointNode* to);
	void ResetNodes();
	void DeleteNodes();

	std::vector<WaypointNode*> GetPathNodes();

	PatrolNode* currentPatrolNode;

private:
	std::vector<WaypointNode*> open;
	std::vector<WaypointNode*> closed;
	std::vector<WaypointNode*> waypointNodes;
	// Array of nodes on the path from goal to start.
	std::vector<WaypointNode*> pathNodes;
	std::vector<PatrolNode*> patrolNodes;
};

