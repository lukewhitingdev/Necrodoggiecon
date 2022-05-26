#pragma once
/*****************************************************************//**
 * \file   CAINode.h
 * \brief  Header containing all the nodes used by the AI.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
class CTile;
#include "Cerberus/Core/Utility/Vector3.h"
#include <iostream>
#include <vector>
/**
 * Waypoint node struct containing the waypoint, parent waypoint, neighbours and the costs.
 */
struct WaypointNode
{
	CTile* waypoint = nullptr;
	CTile* parentWaypoint = nullptr;
	std::vector<WaypointNode*> neighbours;
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
};

/**
 * Patrol node struct containing the position, closest waypoint and the next patrol node.
 */
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