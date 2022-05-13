#pragma once
/*****************************************************************//**
 * \file   Pathfinding.h
 * \brief  Class that handles all the necessary functions and variables for the AI to navigate through any level.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#include "CAINode.h"

/**
 * Pathfinding class to handle all the pathfinding for the AI.
 */
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

