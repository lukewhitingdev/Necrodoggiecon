/*****************************************************************//**
 * \file   CAIController.cpp
 * \brief  All the functions needed to control the AI.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/
#include "CAIController.h"
#include "Cerberus/Core/Utility/CWorldManager.h"

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

	obstacles = CWorldManager::GetWorld()->GetAllObstacleTiles();
	sizeOfTiles = tileScale * obstacles[0]->GetScale().x;

	
	tiles = CWorldManager::GetWorld()->GetAllWalkableTiles();
	int randIndex = rand() % tiles.size();
	SetPosition(tiles[randIndex]->GetPosition());
	aiPosition = GetPosition();	


	PatrolNode* patrolPoint1 = new PatrolNode(Vector3{ 1500.0f, 300.0f, 0.0f });
	PatrolNode* patrolPoint2 = new PatrolNode(Vector3{ 1000.0f, 1300.0f, 0.0f });
	PatrolNode* patrolPoint3 = new PatrolNode(Vector3{ 500.0f, 300.0f, 0.0f });

	patrolPoint1->nextPatrolNode = patrolPoint2;
	patrolPoint2->nextPatrolNode = patrolPoint3;
	patrolPoint3->nextPatrolNode = patrolPoint1;

	SetScale(Vector3{ 0.6f, 0.6f, 0.6f });
	viewFrustrum->viewSprite->SetScale(GetScale() * 0.1f);

	std::vector<PatrolNode*> patrolPoints = { patrolPoint1, patrolPoint2, patrolPoint3 };

	pathing = new Pathfinding(tiles);
	pathing->SetPatrolNodes(patrolPoints);
	pathing->currentPatrolNode = pathing->FindClosestPatrolNode(aiPosition);

	std::function<void()> CanHearLambda = [&]()
	{
		std::vector<CEmitter*> audioEmitters = AudioController::GetAllEmittersWithinRange(aiPosition);
		float closestDistance = 100000000.0f;
		CEmitter* closestEmitter = nullptr;
		if (audioEmitters.size() != 0)
		{
			for (CEmitter* emitter : audioEmitters)
			{
				float distanceToEmitter = aiPosition.DistanceTo(emitter->position);
				if (distanceToEmitter < closestDistance)
				{
					closestDistance = distanceToEmitter;
					closestEmitter = emitter;
				}
			}
			positionToInvestigate = closestEmitter->position;
			SetCurrentState(InvestigateState::getInstance());
		}
	};

	EventSystem::AddListener("soundPlayed", CanHearLambda);

	currentState = &PatrolState::getInstance();
	SetCurrentState(PatrolState::getInstance());
}

/**
 * .
 * 
 * \param deltaTime
 */
void CAIController::Update(float deltaTime)
{
	// Set the local variable for the AI position.
	aiPosition = GetPosition();

	currentState->Update(this);
	// Run the finite state machine
	
	PlayerCharacter* closestPlayer = nullptr;

	if (currentState != &AttackState::getInstance())
	{
		if (players.size() > 0)
		{
			// Check each player.
			for (PlayerCharacter* player : players)
			{
				// Check if the AI can see the player.
				if (CanSee(player->GetPosition()) == true)
				{
					// If the AI can see the player then chase it.
					SetCurrentState(ChaseState::getInstance());
				}
			}
		}
	}

	currentState->Update(this);

	// If the AI is not pathfinding or searching then check for collisions with obstacles.
	if (currentState != &PatrolState::getInstance() && currentState != &SearchState::getInstance())
		heading += CollisionAvoidance();
	
	// Move the AI if it is not lost
	if (currentState != &SearchState::getInstance())
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

/**
 * Moves the character position using acceleration, force, mass and velocity.
 * 
 * \param deltaTime Time between frames.
 * \param deltaTime
 */
void CAIController::Movement(float deltaTime)
{
	// This is just some simple physics to move the AI.
	Vector3 force = (heading * aiSpeed) - velocity;

	acceleration = force / aiMass;

	velocity += acceleration * deltaTime;

	velocity.Truncate(aiSpeed);

	aiPosition += velocity * deltaTime;
}

/**
 * Finds the closest obstacle and calculates the vector to avoid it.
 * 
 * \return Returns a Vector3 that is the direction to avoid the obstacle.
 */
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

/**
 * Maths magic that determines whether the player is in view.
 * 
 * \param posOfObject Vector3 representing the position of the object to see.
 * \return Returns a boolen determining whether the objct is in view.
 */
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

void CAIController::CanHear()
{
	AudioController::GetAllEmittersWithinRange(aiPosition);
}

/**
 * Sets the path nodes for the AI.
 * 
 * \param nodes Vector array of waypoint nodes to set.
 */
void CAIController::SetPathNodes(std::vector<WaypointNode*> nodes)
{
	pathNodes = nodes;
}

/**
 * Moves the direction of the character towards the next point in the path.
 * 
 */
void CAIController::Patrolling()
{
	// If the AI has reached the patrol node.
	if (aiPosition.DistanceTo(pathing->currentPatrolNode->position) <= 10.0f)
	{
		// Set the new patrol node as the next one on the list.
		pathing->currentPatrolNode = pathing->currentPatrolNode->nextPatrolNode;

		// Set the state to pathfinding.
		SetCurrentState(PatrolState::getInstance());

		// Seek to the current patrol node.
		heading = Seek(pathing->currentPatrolNode->position);
		pathing->DeleteNodes();
		
	}
	else
	{
		// If at the closest waypoint node to the patrol node then seek towards the patrol node.
		if (currentCount == -1)
		{
			heading = Seek(pathing->currentPatrolNode->position);
			pathing->DeleteNodes();
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

/**
 * Spin on the spot trying to find the player.
 * 
 */
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



void CAIController::Investigating(Vector3 positionOfInterest)
{
	// If the AI has reached the patrol node.
	if (aiPosition.DistanceTo(positionOfInterest) <= 10.0f)
	{
		// Set the state to searching.
		SetCurrentState(SearchState::getInstance());
		pathing->DeleteNodes();

	}
	else
	{
		// If at the closest waypoint node to the patrol node then seek towards the patrol node.
		if (currentCount == -1)
		{
			heading = Seek(positionOfInterest);
			pathing->DeleteNodes();
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

/**
 * Seek towards the player and if it gets close then switch to the attacking state.
 */
void CAIController::ChasePlayer(PlayerCharacter* player)
{
	if (aiPosition.DistanceTo(player->GetPosition()) < 10.0f)
	{
		SetCurrentState(AttackState::getInstance());
		playerToKill = player;
	}
	else
	{
		heading = Seek(player->GetPosition());
	}
}

/**
 * Attack the player using the weapon attached.
 * 
 * \param player Player to attack.
 */
void CAIController::AttackPlayer(PlayerCharacter* player)
{
	playersController[0]->Unpossess();
	Engine::DestroyEntity(player);
	players = Engine::GetEntityOfType<PlayerCharacter>();
}

/**
 * Returns the velocity change needed to reach the target position.
 * 
 * \param TargetPos Vector3 representing the position for the AI to go.
 * \return Returns the direction to the target position.
 */
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

/**
 * Sets the path between the closest waypoint to the character and the closest waypoint to the target patrol node.
 * 
 */
void CAIController::SetPath()
{
	pathing->SetPath(aiPosition, pathing->currentPatrolNode->closestWaypoint);
	SetPathNodes(pathing->GetPathNodes());
	currentCount = (int)pathNodes.size() - 1;
}

void CAIController::SetPath(Vector3 endPosition)
{
	pathing->SetPath(aiPosition, pathing->FindClosestWaypoint(endPosition));
	SetPathNodes(pathing->GetPathNodes());
	currentCount = (int)pathNodes.size() - 1;
}

void CAIController::SetCurrentState(State& state)
{
	currentState->Exit(this);  // do stuff before we change state
	currentState = &state;  // actually change states now
	currentState->Enter(this); // do stuff after we change state
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
