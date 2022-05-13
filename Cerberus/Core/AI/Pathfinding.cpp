/*****************************************************************//**
 * \file   Pathfinding.cpp
 * \brief  All the necessary functions to help any AI to traverse any level.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#include "Pathfinding.h"

/**
 * Constructor that sets the waypoints.
 * 
 * \param waypoints Vector array of waypoints to set.
 */
Pathfinding::Pathfinding(std::vector<CTile*> waypoints)
{
	// Create a waypoint node for each waypoint passed in.
	for (CTile* waypoint : waypoints)
	{
		WaypointNode* waypointNode = new WaypointNode();
		waypointNode->waypoint = waypoint;

		waypointNodes.push_back(waypointNode);
	}

	currentPatrolNode = nullptr;
}

/**
 * Sets the patrol nodes and the closest waypoint to each node.
 * 
 * \param nodes Vector array of patrol nodes.
 */
void Pathfinding::SetPatrolNodes(std::vector<PatrolNode*> nodes)
{
	patrolNodes = nodes;
	// Find the closest waypoint to each patrol pointy.
	for (PatrolNode* node : patrolNodes)
	{
		node->closestWaypoint = waypointNodes[0];
		for (WaypointNode* waypointNode : waypointNodes)
		{
			if (node->position.DistanceTo(waypointNode->waypoint->GetPosition()) < node->position.DistanceTo(node->closestWaypoint->waypoint->GetPosition()))
			{
				node->closestWaypoint = waypointNode;
			}
		}
	}
}

/**
 * Finds the closest waypoint to the position passed in.
 * 
 * \param position Vector3 of the position.
 * \return Returns a pointer to the closest waypoint.
 */
WaypointNode* Pathfinding::FindClosestWaypoint(Vector3 position)
{
	WaypointNode* closestWaypoint = nullptr;
	closestWaypoint = waypointNodes[0];
	// Find the closest waypoint.
	for (WaypointNode* waypointNode : waypointNodes)
	{
		if (position.DistanceTo(waypointNode->waypoint->GetPosition()) < position.DistanceTo(closestWaypoint->waypoint->GetPosition()))
		{
			closestWaypoint = waypointNode;
		}
	}
	return closestWaypoint;
}

/**
 * Finds the closest patrol node to the position passed in.
 * 
 * \param position Vector3 representing the position.
 * \return Return a pointer to the closest patrol node.
 */
PatrolNode* Pathfinding::FindClosestPatrolNode(Vector3 position)
{
	PatrolNode* closestPatrolNode = new PatrolNode(Vector3{ 10000.0f, 10000.0f, 0.0f });
	for (PatrolNode* node : patrolNodes)
	{
		if (position.DistanceTo(node->position) < position.DistanceTo(closestPatrolNode->position))
		{
			closestPatrolNode = node;
		}
	}
	return closestPatrolNode;
}

/**
 * Gets the closest waypoint to be passed in with the goal waypoint to the calculate path function.
 * 
 * \param currentPosition Vector3 of the position .
 * \param goalWaypoint Waypoint pointer of the goal waypoint.
 */
void Pathfinding::SetPath(Vector3 currentPosition, WaypointNode* goalWaypoint)
{
	DeleteNodes();
	
	WaypointNode* closestWaypoint = FindClosestWaypoint(currentPosition);

	// Caluclate the path between the closest waypoint and the patrol node.
	CalculatePath(closestWaypoint, goalWaypoint);
}

/**
 * A* to calculate the shortest path between 2 waypoints.
 * 
 * \param start Start waypoint.
 * \param goal End waypoint.
 */
void Pathfinding::CalculatePath(WaypointNode* start, WaypointNode* goal)
{
	// Place start node onto open list.
	open.push_back(start);

	// Set the current node as the start node.
	WaypointNode* current = open[0];

	// While the open list is not empty.
	while (open.empty() != true)
	{
		// Set the current node to the open node.
		if (current->waypoint == start->waypoint)
		{
			current = open[0];
			// Set the g cost as 0.
			current->gCost = CalculateCost(current, start);
			// Set the h cost as the distance to goal.
			current->hCost = CalculateCost(current, goal);

			current->fCost = current->gCost + current->hCost;


			// Remove the node from the open list.
			open.erase(open.begin());
		}
		else
		{
			// If the current node is not the first node.
			int bestNodeIndex = 0;
			for (int i = 0; i < open.size(); i++)
			{
				// If the f cost is less than the current f cost then set the current node to that node and remove it from the open list.
				if (open[i]->fCost == open[bestNodeIndex]->fCost)
				{
					if (open[i]->hCost < open[bestNodeIndex]->hCost)
						bestNodeIndex = i;
				}
				else if (open[i]->fCost < open[bestNodeIndex]->fCost)
				{
					bestNodeIndex = i;
				}
			}
			current = open[bestNodeIndex];
			open.erase(open.begin() + bestNodeIndex);
		}


		// Found the best node at this stage so put it in the closed list.
		closed.push_back(current);

		// If this is the goal node then stop.
		if (current->waypoint == goal->waypoint)
			break;

		// Neighbour IDs of the current waypoint.
		std::vector<int> _neighboursID = current->waypoint->GetConnectedTiles();

		if (current->neighbours.size() == 0)
		{
			// Set the neighbour nodes of the current node.
			for (int i = 0; i < _neighboursID.size(); i++)
			{
				for (WaypointNode* node : waypointNodes)
				{
					if (_neighboursID[i] == node->waypoint->GetNavID())
					{
						current->neighbours.push_back(node);
						break;
					}
				}
			}
		}
		// Loop through each neighbour node of the current node
		for (WaypointNode* neighbour : current->neighbours)
		{
			bool available = true;
			// Loop through each node on the closed list to make sure the neighbour node is not on the closed list.
			for (WaypointNode* node : closed)
			{
				if (node->waypoint == neighbour->waypoint)
				{
					available = false;
					break;
				}
			}

			// If the neighbour node is not on the closed list. 
			if (available == true)
			{
				// Calculate the distance from the neighbour node and the start node.
				//float gCost = CalculateCost(neighbour->waypoint->GetPosition().x, neighbour->waypoint->GetPosition().y, start->waypoint->GetPosition().x, start->waypoint->GetPosition().y);
				float gCost = current->gCost + (float)tileScale * 2.0f;
				// Calculate the distance from the neighbour node and the goal node.
				float hCost = CalculateCost(neighbour, goal);
				//hCost = CalculateCost(neighbour->waypoint->GetPosition().x, neighbour->waypoint->GetPosition().y, goal->waypoint->GetPosition().x, goal->waypoint->GetPosition().y);
				neighbour->gCost = gCost;
				neighbour->hCost = hCost;
				neighbour->fCost = neighbour->gCost + neighbour->hCost;

				// Set the neighbour parent waypoint as the current waypoint
				neighbour->parentWaypoint = current->waypoint;

				// If the open list is not empty.
				if (open.size() != 0)
				{
					// Loop through the open list.
					for (int i = 0; i < open.size(); i++)
					{
						// If the neighbour waypoint is on the open list and the f cost is less then update that node on the open list.
						if (open[i]->waypoint == neighbour->waypoint)
						{
							if (open[i]->fCost > neighbour->fCost)
								open[i] = neighbour;
							break;
						}
						// If the nieghbour node is not on the open list then add it to it.
						else if (i == open.size() - 1)
						{

							open.push_back(neighbour);
						}
					}
				}
				// If the open list is empty add the neighbour node to the list.
				else
				{
					open.push_back(neighbour);
				}
			}
		}
	}

	// Set the current node to the end node on the closed list.
	current = goal;

	// Loop through the parent nodes starting with the current node till the start node.
	while (current->waypoint != start->waypoint)
	{
		// Push the current node onto the path nodes array.
		pathNodes.push_back(current);

		// Loop though all the waypoint nodes.
		for (WaypointNode* node : closed)
		{
			// if this node is the parent node then set if as the current node.
			if (node->parentWaypoint != nullptr || node == start)
			{
				if (node->waypoint == current->parentWaypoint)
				{
					current = node;
					break;
				}
			}

		}
	}

	// Finally push the final node onto the array of path nodes. 
	pathNodes.push_back(current);
}

/**
 * Calculates the euclidean distance between 2 waypoints.
 * 
 * \param from Waypoint to calculate from.
 * \param to Waypoint to calculate to.
 * \return Returns a float representing the distance.
 */
float Pathfinding::CalculateCost(WaypointNode* from, WaypointNode* to)
{
	float costX = std::abs(to->waypoint->GetPosition().x - from->waypoint->GetPosition().x);
	float costY = std::abs(to->waypoint->GetPosition().y - from->waypoint->GetPosition().y);

	float cost = costX + costY;
	return cost;
}

/**
 * Resets the g and h costs to 10 million.
 * 
 */
void Pathfinding::ResetNodes()
{
	for (WaypointNode* node : waypointNodes)
	{
		node->gCost = 10000000.0f;
		node->hCost = 10000000.0f;
	}
}

/**
 * Calls the reset nodes function and clears the open, closed and path nodes arrays.
 * 
 */
void Pathfinding::DeleteNodes()
{
	ResetNodes();
	open.clear();
	closed.clear();
	pathNodes.clear();
}

/**
 * Gets the path nodes vector array.
 * 
 * \return Returns the path nodes.
 */
std::vector<WaypointNode*> Pathfinding::GetPathNodes()
{
	return pathNodes;
}
