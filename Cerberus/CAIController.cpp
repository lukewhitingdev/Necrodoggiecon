#include "CAIController.h"

CAIController::CAIController()
{
	Debug::Log("init AI class!\n");

	viewFrustrum->SetScale(Vector3{ (aiRange/128.0f) + 2.0f, (aiRange / 128.0f) + 2.0f, 1.0f });
	viewFrustrum->SetPosition(GetPosition());

	sprite = AddComponent<CSpriteComponent>();
	sprite->LoadTexture("Resources\\birb.dds");
	sprite->SetRenderRect(XMUINT2(128, 128));
	sprite->SetSpriteSize(XMUINT2(128, 128));
	sprite->SetScale(Vector3{ 1.0f, 1.0f, 1.0f });

	sprite->SetTint(XMFLOAT4(rand() % 2 * 0.5f, rand() % 2 * 0.5f, rand() % 2 * 0.5f, 0)); 

	currentCount = 0;
	currentPatrolNode = nullptr;

	velocity = { 0.0f, 0.0f, 0.0f };
	heading = { 0.0f, 0.0f, 0.0f };
	acceleration = { 0.0f, 0.0f, 0.0f };

	obstacles = CWorld::GetAllObstacleTiles();
	sizeOfTiles = tileScale * obstacles[0]->GetScale().x;

	tiles = CWorld::GetAllWalkableTiles();
	SetPosition(tiles[102]->GetPosition());
	aiPosition = GetPosition();	


	PatrolNode* patrolPoint1 = new PatrolNode(Vector3{ 500.0f, 200.0f, 0.0f });
	PatrolNode* patrolPoint2 = new PatrolNode(Vector3{ -500.0f, 300.0f, 0.0f });
	PatrolNode* patrolPoint3 = new PatrolNode(Vector3{ -500.0f, -200.0f, 0.0f });

	patrolPoint1->nextPatrolNode = patrolPoint2;
	patrolPoint2->nextPatrolNode = patrolPoint3;
	patrolPoint3->nextPatrolNode = patrolPoint1;

	SetScale(Vector3{ 0.6f, 0.6f, 0.6f });
	viewFrustrum->viewSprite->SetScale(GetScale() * 0.1f);

	std::vector<PatrolNode*> patrolPoints = { patrolPoint1, patrolPoint2, patrolPoint3 };

	SetPatrolNodes(patrolPoints, tiles);
}

void CAIController::Update(float deltaTime)
{
	// Set the local variable for the AI position.
	aiPosition = GetPosition();

	// Run the finite state machine
	StateMachine(deltaTime);
	
	// Move the AI if it is not lost
	if (currentState != STATE::SEARCH)
		Movement(deltaTime);

	// Temp code for the arrow sprite so I know where the AI is looking. 
	{
		Vector3 velocityCopy = velocity;
		Vector3 view = velocityCopy.Normalize();
		float offset = 128.0f * viewFrustrum->viewSprite->GetScale().x;

		viewFrustrum->SetPosition(GetPosition() + (view * (offset + (128.0f * GetScale().x * 0.5f))));

		Vector3 up = { 0.0f, 1.0f, 0.0f };

		float dot = up.Dot(view);
		float det = up.x * view.y - up.y * view.x;

		float angle = atan2f(det, dot);
		this->SetRotation(angle);
		viewFrustrum->SetRotation(angle);
		viewFrustrum->SetPosition(Vector3{ viewFrustrum->GetPosition().x, viewFrustrum->GetPosition().y, 0.0f });
	}

	// Make sure the AI is on a 2D vector.
	aiPosition.z = 0.0f;

	// Set the position of the entity to the local variable for the AI position.
	SetPosition(aiPosition);
}

/* Moves the character position using acceleration, force, mass and velocity. */
void CAIController::Movement(float deltaTime)
{
	// This is just some simple physics to move the AI.
	Vector3 force = (heading * aiSpeed) - velocity;

	acceleration = force / aiMass;

	velocity += acceleration * deltaTime;

	velocity.Truncate(aiSpeed);

	aiPosition += velocity * deltaTime;
}

/* Finds the closest obstacle and calculates the vector to avoid it. */
Vector3 CAIController::CollisionAvoidance()
{
	// Initialize the return value for the avoidance vector.
	Vector3 avoidance = Vector3{ 0.0f, 0.0f, 0.0f };
	
	// Initialize the closest obstable with the first obstacle temp.
	CTile* closestObstacle = obstacles[0];
	Vector3 centerOfClosestObstacle = Vector3{ closestObstacle->GetPosition().x + (sizeOfTiles * 0.5f), closestObstacle->GetPosition().y + (sizeOfTiles * 0.5f), 0.0f };

	// Find the closest obstacle to the AI using the center of tiles because get position finds the bottom left corner of the tile. 
	for (CTile* obstacle : obstacles)
	{
		Vector3 centerOfObstacle = Vector3{ obstacle->GetPosition().x + (sizeOfTiles * 0.5f), obstacle->GetPosition().y + (sizeOfTiles * 0.5f), 0.0f };
		if (aiPosition.DistanceTo(centerOfObstacle) < aiPosition.DistanceTo(centerOfClosestObstacle))
		{
			closestObstacle = obstacle;
			centerOfClosestObstacle = centerOfObstacle;
		}
	}

	// Get the radius of the AI.
	float widthRadius = width * GetScale().x;
	float heightRadius = height * GetScale().y;

	// Check if the AI collides with the closest obstacle.
	if (aiPosition.x + widthRadius > closestObstacle->GetPosition().x &&
		aiPosition.x - widthRadius < closestObstacle->GetPosition().x &&
		aiPosition.y + heightRadius > closestObstacle->GetPosition().y &&
		aiPosition.y - heightRadius < closestObstacle->GetPosition().y)
	{
		// Calculate a vector in the facing direction of the AI.
		Vector3 ahead = velocity;
		ahead.Normalize();
		ahead *= 10.0f;

		// Find the vector to the obstacle.
		Vector3 test1 = ahead;
		Vector3 test2 = centerOfClosestObstacle - aiPosition;

		// Calculate the vector needed to avoid the obstacle.
		avoidance = test1 - test2;
		avoidance.Normalize();
		avoidance *= 5000.0f;
		avoidance.z = 0.0f;
	}
	return avoidance;
}

/* Maths magic that determines whether the player is in view. */
bool CAIController::CanSee(Vector3 posOfObject)
{
	// Calculate the direction the AI is looking.
	Vector3 velocityCopy = velocity;
	Vector3 view = velocityCopy.Normalize();

	// Calculate the direction to the position passed in.
	Vector3 viewToPlayer = posOfObject - aiPosition;
	float distanceToPlayer = viewToPlayer.Magnitude();
	
	viewToPlayer = viewToPlayer.Normalize();
	
	// Find the angle between the AI view and the player.
	float dotProduct = view.Dot(viewToPlayer);
	float pi = atanf(1) * 4;
	float degreeAngle = dotProduct * (180.0f / pi);

	float viewingAngle = (aiViewAngle * (-2.0f / 3.0f)) + 60.0f;

	// Check the player is the viewing range of the AI.
	if (degreeAngle > viewingAngle && distanceToPlayer < aiRange)
	{
		CTile* closestObstacle = obstacles[0];
		Vector3 centerOfClosestObstacle = Vector3{ 0.0f, 0.0f, 0.0f };

		// Create a ray cast to the player and find the number of checks needed to find an obstacle.
		float numberOfCasts = distanceToPlayer / sizeOfTiles;
		for (float i = 0; i < numberOfCasts; i++)
		{
			// Calculate the check position for each check along the ray cast.
			Vector3 pointToCheck = aiPosition + (viewToPlayer * sizeOfTiles * i);
			pointToCheck += Vector3{ sizeOfTiles * 0.5f, sizeOfTiles * 0.5f, 0.0f };
			pointToCheck.z = 0.0f;

			// Find the closest obstacle to the check position.
			for (CTile* obstacle : obstacles)
			{
				Vector3 centerOfObstacle = Vector3{ obstacle->GetPosition().x + (sizeOfTiles * 0.5f), obstacle->GetPosition().y + (sizeOfTiles * 0.5f), 0.0f };
				if (pointToCheck.DistanceTo(centerOfObstacle) < pointToCheck.DistanceTo(centerOfClosestObstacle))
				{
					closestObstacle = obstacle;
					centerOfClosestObstacle = centerOfObstacle;
				}
			}

			// If the check position is on an obstacle then reutrn false.
			if (pointToCheck.x > closestObstacle->GetPosition().x &&
				pointToCheck.x < closestObstacle->GetPosition().x + sizeOfTiles &&
				pointToCheck.y > closestObstacle->GetPosition().y &&
				pointToCheck.y < closestObstacle->GetPosition().y + sizeOfTiles)
			{
				return false;
			}

		}
		return true;
	}
	return false;
}

/* Initialize the patrol nodes and waypoints. */
void CAIController::SetPatrolNodes(std::vector<PatrolNode*> nodes, std::vector<CTile*> waypoints)
{
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
		node->closestWaypoint = waypointNodes[0];
		for (WaypointNode* waypointNode : waypointNodes)
		{
			if (node->position.DistanceTo(waypointNode->waypoint->GetPosition()) < node->position.DistanceTo(node->closestWaypoint->waypoint->GetPosition()))
			{
				node->closestWaypoint = waypointNode;
			}
		}
	}

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
		if (aiPosition.DistanceTo(node->position) < aiPosition.DistanceTo(closestPatrolNode->position))
		{
			closestPatrolNode = node;
		}
	}
	return closestPatrolNode;
}

/* Calls the relevant function based on the current state. */
void CAIController::StateMachine(float deltaTime)
{
	Vector3 closestPlayerPosition = { INFINITY, INFINITY, INFINITY };
	testCharacter* closestPlayer = nullptr;


	if (currentState != STATE::ATTACK)
	{
		if (players.size() > 0)
		{
			// Check each player.
			for (testCharacter* player : players)
			{
				// Check if the AI can see the player.
				if (CanSee(player->GetPosition()) == true)
				{
					// If the AI can see the player then chase it.
					currentState = STATE::CHASE;

					// Reset the timer for the searching.
					searchTimer = maxSearchTime;

					// Find if the player is the closest in view.
					if (aiPosition.DistanceTo(player->GetPosition()) < aiPosition.DistanceTo(closestPlayerPosition))
					{
						closestPlayer = player;
						closestPlayerPosition = closestPlayer->GetPosition();
					}

					// Set the player to chase to the closest player in view.
					playerToChase = closestPlayer;
				}
			}

			// If no players are in view.
			if (closestPlayer == nullptr)
			{
				// Create a delay for the AI to find the player if it loses track of it.
				if (searchTimer > 0.0f)
				{
					// Set the AI to search for the player.
					currentState = STATE::SEARCH;
					searchTimer -= deltaTime;

					// If the timer is up then go back to pathfinding.
					if (searchTimer < 0.02f)
						currentState = STATE::PATHFINDING;
				}
			}
		}
	}

	switch (currentState)
	{
	case STATE::PATROL:
		Patrolling();
		break;
	case STATE::PATHFINDING:
		SetPath(currentPatrolNode->closestWaypoint);
		break;
	case STATE::CHASE:
		ChasePlayer(playerToChase);
		break;
	case STATE::ATTACK:
		AttackPlayer(playerToKill);
		break;
	case STATE::COVER:
		GetIntoCover();
		break;
	case STATE::SEARCH:
		SearchForPlayer();
		break;
	default:

		break;
	}

	// If the AI is not pathfinding or searching then check for collisions with obstacles.
	if (currentState != STATE::PATROL && currentState != STATE::SEARCH)
		heading += CollisionAvoidance();
}

/* Moves the direction of the character towards the next point in the path. */
void CAIController::Patrolling()
{
	// If the AI has reached the patrol node.
	if (aiPosition.DistanceTo(currentPatrolNode->position) <= 10.0f)
	{
		// Set the new patrol node as the next one on the list.
		currentPatrolNode = currentPatrolNode->nextPatrolNode;

		// Set the state to pathfinding.
		currentState = STATE::PATHFINDING;

		// Seek to the current patrol node.
		heading = Seek(currentPatrolNode->position);
		DeleteNodes();
		
	}
	else
	{
		// If at the closest waypoint node to the patrol node then seek towards the patrol node.
		if (currentCount == -1)
		{
			heading = Seek(currentPatrolNode->position);
			DeleteNodes();
		}
		// Else seek to the next waypoint node.
		else
		{
			heading = Seek(pathNodes[currentCount]->waypoint->GetPosition());

			// If close to the waypoint node then set the next waypoint node from the list.
			if (aiPosition.DistanceTo(pathNodes[currentCount]->waypoint->GetPosition()) <= (((float)tileScale) * tiles[0]->GetScale().x))
			{
				currentCount--;
			}
		}
	}
}

/* Spin on the spot trying to find the player. */
void CAIController::SearchForPlayer()
{
	// Set the direction the AI is facing.
	Vector3 velocityCopy = velocity;
	Vector3 view = velocityCopy.Normalize();

	// Set the origin vector for reference.
	Vector3 up = { 0.0f, 1.0f, 0.0f };

	// Find the dot product and determinent between the facing direction and the origin.
	float dot = view.Dot(up);
	float det = view.x * up.y - view.y * up.x;

	// Find the angle between the 2 vectors.
	float angle = atan2f(det, dot);

	// Increase the angle by the rotation speed.
	angle += rotationSpeed;

	// Find the sine and cosine of the angle.
	float cossy = cos(angle);
	float sinny = sin(angle);

	// Calculate the new facing direction of the AI.
	float x = up.x * cossy - up.y * sinny;
	float y = up.x * sinny + up.y * cossy;

	// Set the velocity as the new facing direction.
	velocity = Vector3{ -x, y, 0.0f };
	
}

// Seek towards the player and if it gets close then clart it. To be overriden by the melee and ranged AIs in the future.
void CAIController::ChasePlayer(testCharacter* player)
{
	if (aiPosition.DistanceTo(player->GetPosition()) < 10.0f)
	{
		currentState = STATE::ATTACK;
		playerToKill = player;
	}
	else
	{
		heading = Seek(player->GetPosition());
	}
}

// Absolutely CLART the player off the face of this virtual plane.
void CAIController::AttackPlayer(testCharacter* player)
{
	Engine::DestroyEntity(player);
	players = Engine::GetEntityOfType<testCharacter>();
	currentState = STATE::PATHFINDING;
	//EventSystem::TriggerEvent("GameOver");
}



/* Returns the velocity change needed to reach the target position. */
Vector3 CAIController::Seek(Vector3 TargetPos)
{
	Vector3 ToTarget = TargetPos - aiPosition;

	double dist = ToTarget.Magnitude();

	if (dist > 0)
	{
		Vector3 DesiredVelocity = Vector3(TargetPos - aiPosition).Normalize() * aiSpeed;
		return (DesiredVelocity - velocity);
	}
	return Vector3{ 0.0f, 0.0f, 0.0f };
}

/* Sets the path betqween the closest waypoint to the character and the closest waypoint to the target patrol node. */
void CAIController::SetPath(WaypointNode* goalWaypoint)
{
	DeleteNodes();
	WaypointNode* closestWaypoint = nullptr;
	closestWaypoint = waypointNodes[0];
	// Find the closest waypoint.
	for (WaypointNode* waypointNode : waypointNodes)
	{
		if (aiPosition.DistanceTo(waypointNode->waypoint->GetPosition()) < aiPosition.DistanceTo(closestWaypoint->waypoint->GetPosition()))
		{
			closestWaypoint = waypointNode;
		}
	}

	// Caluclate the path between the closest waypoint and the patrol node.
	CalculatePath(closestWaypoint, goalWaypoint);
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

void CAIController::SetRotationSpeed(float speed)
{
	rotationSpeed = speed;
}

float CAIController::GetRotationSpeed()
{
	return rotationSpeed;
}

void CAIController::SetSearchTime(float time)
{
	maxSearchTime = time;
}

float CAIController::GetSearchTime()
{
	return maxSearchTime;
}

void CAIController::SetHealth(float health)
{
	aiHealth = health;
}

float CAIController::GetHealth()
{
	return aiHealth;
}

void CAIController::SetSpeed(float speed)
{
	aiSpeed = speed;
}

float CAIController::GetSpeed()
{
	return aiSpeed;
}

void CAIController::SetMass(float mass)
{
	aiMass = mass;	
}

float CAIController::GetMass()
{
	return aiMass;
}

void CAIController::SetRange(float range)
{
	aiRange = range;
}

float CAIController::GetRange()
{
	return aiRange;
}

void CAIController::SetViewAngle(float angle)
{
	aiViewAngle = angle;
}

float CAIController::GetViewAngle()
{
	return aiViewAngle;
}

void CAIController::SetWidth(float wide)
{
	width = wide;
}

float CAIController::GetWidth()
{
	return width;
}

void CAIController::SetHeight(float high)
{
	height = high;
}

float CAIController::GetHeight()
{
	return height;
}
