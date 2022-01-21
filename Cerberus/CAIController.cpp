#include "CAIController.h"

CAIController::CAIController()
{
	Debug::Log("init AI class!\n");


	player->SetPosition(Vector3{-500.0f, 100.0f, 0.0f});
	player->SetScale(Vector3{ 0.2f, 0.2f, 0.2f });

	viewFrustrum->SetScale(Vector3{ (aiRange/128.0f) + 2.0f, (aiRange / 128.0f) + 2.0f, 1.0f });
	viewFrustrum->SetPosition(GetPosition());

	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\birb.dds");
	sprite->SetRenderRect(XMUINT2(128, 128));
	sprite->SetSpriteSize(XMUINT2(128, 128));
	sprite->SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

	sprite->SetTint(XMFLOAT4(rand() % 2 * 0.5f, rand() % 2 * 0.5f, rand() % 2 * 0.5f, 0)); sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\birb.dds");
	sprite->SetRenderRect(XMUINT2(128, 128));
	sprite->SetSpriteSize(XMUINT2(128, 128));

	sprite->SetTint(XMFLOAT4(rand() % 2 * 0.5f, rand() % 2 * 0.5f, rand() % 2 * 0.5f, 0));


	currentCount = 0;
	currentPatrolNode = nullptr;

	velocity = { 0.0f, 0.0f, 0.0f };
	heading = { 0.0f, 0.0f, 0.0f };
	acceleration = { 0.0f, 0.0f, 0.0f };

	tiles = CWorld::GetAllWalkableTiles();
	SetPosition(tiles[6]->GetPosition());
	position = GetPosition();	

	/*std::vector<Waypoint*> waypoints;

	std::vector<int> neighbours = { 1, 4 };
	Waypoint* topLeft = new Waypoint(0, Vector3{ -300.0f, 100.0f, 0.0f }, neighbours);

	waypoints.emplace_back(topLeft);

	neighbours = { 0, 2, 5 };
	Waypoint* topMiddleLeft = new Waypoint(1, Vector3{ -100.0f, 100.0f, 0.0f }, neighbours);

	waypoints.emplace_back(topMiddleLeft);

	neighbours = { 1, 3, 6 };
	Waypoint* topMiddleRight = new Waypoint(2, Vector3{ 100.0f, 100.0f, 0.0f }, neighbours);

	waypoints.emplace_back(topMiddleRight);

	neighbours = { 2, 7 };
	Waypoint* topRight = new Waypoint(3, Vector3{ 300.0f, 100.0f, 0.0f }, neighbours);

	waypoints.emplace_back(topRight);

	neighbours = { 0, 5 };
	Waypoint* bottomLeft = new Waypoint(4, Vector3{ -300.0f, -100.0f, 0.0f }, neighbours);

	waypoints.emplace_back(bottomLeft);

	neighbours = { 1, 4, 6 };
	Waypoint* bottomMiddleLeft = new Waypoint(5, Vector3{ -100.0f, -100.0f, 0.0f }, neighbours);

	waypoints.emplace_back(bottomMiddleLeft);

	neighbours = { 2, 5, 7 };
	Waypoint* bottomMiddleRight = new Waypoint(6, Vector3{ 100.0f, -100.0f, 0.0f }, neighbours);

	waypoints.emplace_back(bottomMiddleRight);

	neighbours = { 3, 6 };
	Waypoint* bottomRight = new Waypoint(7, Vector3{ 300.0f, -100.0f, 0.0f }, neighbours);

	waypoints.emplace_back(bottomRight);*/

	PatrolNode* patrolPoint1 = new PatrolNode(Vector3{ 500.0f, 200.0f, 0.0f });
	PatrolNode* patrolPoint2 = new PatrolNode(Vector3{ -500.0f, 300.0f, 0.0f });
	PatrolNode* patrolPoint3 = new PatrolNode(Vector3{ -500.0f, -200.0f, 0.0f });

	patrolPoint1->nextPatrolNode = patrolPoint2;
	patrolPoint2->nextPatrolNode = patrolPoint3;
	patrolPoint3->nextPatrolNode = patrolPoint1;

	std::vector<PatrolNode*> patrolPoints = { patrolPoint1, patrolPoint2, patrolPoint3 };

	SetPatrolNodes(patrolPoints, tiles);
}

void CAIController::Update(float deltaTime)
{
	position = GetPosition();
	StateMachine();

	Movement(deltaTime);
	if (player != nullptr)
	{
		if (CanSeePlayer())
		{
			Debug::Log("CAN SEE PLAYER");
			currentState = STATE::CHASE;
		}
		else
		{
			Debug::Log("CAN NOT SEE PLAYER");
		}
	}

	Vector3 velocityCopy = velocity;
	Vector3 view = velocityCopy.Normalize();
	float offset = viewFrustrum->GetScale().x * 128.0f / 2.0f;

	viewFrustrum->SetPosition(GetPosition() + (view * (offset + (128.0f * GetScale().x))));

	Vector3 up = { 0.0f, 1.0f, 0.0f };

	float dot = up.Dot(view);
	float det = up.x * view.y - up.y * view.x;

	float angle = atan2f(det, dot);
	this->SetRotation(angle);
	viewFrustrum->SetRotation(angle);
	viewFrustrum->SetPosition(Vector3{ viewFrustrum->GetPosition().x, viewFrustrum->GetPosition().y, 0.0f });

	position.z = 0.0f;
	SetPosition(position);
}

/* Moves the character position using acceleration, force, mass and velocity. */
void CAIController::Movement(float deltaTime)
{
	Vector3 force = (heading * aiSpeed) - velocity;

	acceleration = force / aiMass;

	velocity += acceleration * deltaTime;

	velocity.Truncate(aiSpeed);

	position += velocity * deltaTime;
}

/* Maths magic that determines whether the player is in view. */
bool CAIController::CanSeePlayer()
{
	Vector3 velocityCopy = velocity;
	Vector3 view = velocityCopy.Normalize();

	Vector3 rightView = Vector3{ view.y, -view.x, 0.0f };

	Vector3 viewToPlayer = player->GetPosition() - position;
	float distanceToPlayer = viewToPlayer.Magnitude();
	
	viewToPlayer = viewToPlayer.Normalize();
	
	float dotProduct = view.Dot(viewToPlayer);
	float pi = atanf(1) * 4;
	float degreeAngle = dotProduct * (180.0f / pi);
	Debug::Log("Angle to player = %f", degreeAngle);

	float viewingAngle = (aiViewAngle * (-2.0f / 3.0f)) + 60;

	if (degreeAngle > viewingAngle && distanceToPlayer < aiRange)
		return true;

	return false;
}

/* Initialize the patrol nodes and waypoints. */
void CAIController::SetPatrolNodes(std::vector<PatrolNode*> nodes, std::vector<CTile*> waypoints)
{
	// Create a waypoint that is really far away.
	std::vector<int> vectorInt = { 0 };
	CTile* farWaypoint = Engine::CreateEntity<CTile>();
	farWaypoint->SetPosition(Vector3{ 10000.0f, 10000.0f, 0.0f });
	WaypointNode* farWaypointNode = new WaypointNode();
	farWaypointNode->waypoint = farWaypoint;

	// Create a waypoint node for each waypoint passed in.
	for (CTile* waypoint : waypoints)
	{
		WaypointNode* waypointNode = new WaypointNode();
		waypointNode->waypoint = waypoint;

		waypointNodes.push_back(waypointNode);
	}

	// Set the patrol nodes to the ones passed in.
	patrolNodes = nodes;

	// Find the closest waypoint to each patrol pointy.
	for (PatrolNode* node : patrolNodes)
	{
		node->closestWaypoint = farWaypointNode;
		for (WaypointNode* waypointNode : waypointNodes)
		{
			if (node->position.DistanceTo(waypointNode->waypoint->GetPosition()) < node->position.DistanceTo(node->closestWaypoint->waypoint->GetPosition()))
			{
				node->closestWaypoint = waypointNode;
			}
		}
	}

	// Cleanup temporary values;
	delete(farWaypointNode);
	vectorInt.clear();

	// Find the closest patrol point to the tank.
	currentPatrolNode = FindClosestPatrolNode();

	// Set the current state as patrol.
	currentState = STATE::PATHFINDING;
}

/* Finds the closest waypoint to each patrol point. */
PatrolNode* CAIController::FindClosestPatrolNode()
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

/* Calls the relevant function based on the current state. */
void CAIController::StateMachine()
{
	switch (currentState)
	{
	case STATE::PATROL:
		Patrolling();
		break;
	case STATE::PATHFINDING:
		SetPath();
		break;
	case STATE::CHASE:
		ChasePlayer();
		break;
	case STATE::ATTACK:
		AttackPlayer();
		break;
	case STATE::COVER:

		break;
	default:

		break;
	}


}

/* Moves the direction of the character towards the next point in the path. */
void CAIController::Patrolling()
{
	if (position.DistanceTo(currentPatrolNode->position) <= 10.0f)
	{
		Debug::Log("Hit patrol node: x=%f, y=%f", currentPatrolNode->position.x, currentPatrolNode->position.y);
		currentPatrolNode = currentPatrolNode->nextPatrolNode;

		currentState = STATE::PATHFINDING;
		heading = Seek(currentPatrolNode->position);
		DeleteNodes();
		
	}
	else
	{
		if (currentCount == -1)
		{
			heading = Seek(currentPatrolNode->position);
			DeleteNodes();
		}
		else
		{
			heading = Seek(pathNodes[currentCount]->waypoint->GetPosition());
			if (position.DistanceTo(pathNodes[currentCount]->waypoint->GetPosition()) <= (((float)tileScale) * 2.0f))
			{
				currentCount--;
			}
		}
	}
}

void CAIController::ChasePlayer()
{
	if (position.DistanceTo(player->GetPosition()) < 10.0f)
	{
		currentState = STATE::ATTACK;
	}
	else
	{
		heading = Seek(player->GetPosition());
	}
}

void CAIController::AttackPlayer()
{
	Engine::DestroyEntity(player);
	player = nullptr;
	currentState = STATE::PATHFINDING;
	//EventSystem::TriggerEvent("GameOver");
}



/* Returns the velocity change needed to reach the target position. */
Vector3 CAIController::Seek(Vector3 TargetPos)
{
	Vector3 ToTarget = TargetPos - position;

	double dist = ToTarget.Magnitude();

	if (dist > 0)
	{
		Vector3 DesiredVelocity = Vector3(TargetPos - position).Normalize() * aiSpeed;
		return (DesiredVelocity - velocity);
	}
	return Vector3{ 0.0f, 0.0f, 0.0f };
}

/* Sets the path betqween the closest waypoint to the character and the closest waypoint to the target patrol node. */
void CAIController::SetPath()
{
	DeleteNodes();
	std::vector<int> base = { 1000000 };
	WaypointNode* closestWaypoint = new WaypointNode();
	CTile* farWaypoint = Engine::CreateEntity<CTile>();
	farWaypoint->SetPosition(Vector3{ 10000.0f, 10000.0f, 0.0f });
	closestWaypoint->waypoint = farWaypoint;
	// Find the closest waypoint.
	for (WaypointNode* waypointNode : waypointNodes)
	{
		if (position.DistanceTo(waypointNode->waypoint->GetPosition()) < position.DistanceTo(closestWaypoint->waypoint->GetPosition()))
		{
			closestWaypoint = waypointNode;
		}
	}

	// Caluclate the path between the closest waypoint and the patrol node.
	CalculatePath(closestWaypoint, currentPatrolNode->closestWaypoint);
}

/* A* algorithm to find the list of waypoints to get from the start node to the target node. */
void CAIController::CalculatePath(WaypointNode* start, WaypointNode* goal)
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
		for (WaypointNode * neighbour : current->neighbours)
		{
			bool available = true;
			// Loop through each node on the closed list to make sure the neighbour node is not on the closed list.
			for (WaypointNode * node : closed)
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
		for (WaypointNode * node : closed)
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

	// Set the current count to be the index of the final node on the list.
	currentCount = (int)pathNodes.size() - 1;

	currentState = STATE::PATROL;
}

/* Calculate the euclidean distance between two points. */
float CAIController::CalculateCost(WaypointNode * from, WaypointNode* to)
{
	float costX = std::abs(to->waypoint->GetPosition().x - from->waypoint->GetPosition().x);
	float costY = std::abs(to->waypoint->GetPosition().y - from->waypoint->GetPosition().y);

	//float euclidenDistance = to->waypoint->GetPosition().DistanceTo(from->waypoint->GetPosition());

	float cost = costX + costY;
	return cost;
}

/* Reset the nodes cost to be a large number. */
void CAIController::ResetNodes()
{
	for (WaypointNode * node : waypointNodes)
	{
		node->gCost = 10000000.0f;
		node->hCost = 10000000.0f;
	}
}

/* Clear all the nodes. */
void CAIController::DeleteNodes()
{
	ResetNodes();
	open.clear();
	closed.clear();
	pathNodes.clear();
}

void CAIController::SetHealth(int health)
{
	aiHealth = health;
}

int CAIController::GetHealth()
{
	return aiHealth;
}

void CAIController::SetSpeed(int speed)
{
	aiSpeed = speed;
}

int CAIController::GetSpeed()
{
	return aiSpeed;
}

void CAIController::SetMass(int mass)
{
	aiMass = mass;	
}

int CAIController::GetMass()
{
	return aiMass;
}

void CAIController::SetRange(int range)
{
	aiRange = range;
}

int CAIController::GetRange()
{
	return aiRange;
}

void CAIController::SetViewAngle(int angle)
{
	aiViewAngle = angle;
}

int CAIController::GetViewAngle()
{
	return aiViewAngle;
}
