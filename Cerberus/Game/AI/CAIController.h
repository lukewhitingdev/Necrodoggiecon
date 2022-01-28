#pragma once
#include "CEntity.h"
#include "Utility/Vector3.h"
#include "CSpriteComponent.h"
#include "CAICharacter.h"
#include <iostream>
#include "CPlayer.h"
#include "testClass.h"
#include "Utility/EventSystem/EventSystem.h"
#include "Environment/CWorld.h"
#include "CAINode.h"
#include "testCharacter.h"
#include "CCharacter.h"

enum class STATE
{
	PATROL,
	PATHFINDING,
	CHASE,
	ATTACK,
	COVER,
	SEARCH
};


class CAIController : public CEntity
{
public:
	CAIController();

	
	void SetRotationSpeed(float speed);
	float GetRotationSpeed();

	void SetSearchTime(float time);
	float GetSearchTime();

	void SetHealth(float health);
	float GetHealth();
	void SetSpeed(float speed);
	float GetSpeed();
	void SetMass(float mass);
	float GetMass();
	void SetRange(float range);
	float GetRange();
	void SetViewAngle(float angle);
	float GetViewAngle();

	void SetWidth(float wide);
	float GetWidth();
	void SetHeight(float high);
	float GetHeight();

	virtual void Update(float deltaTime) override;

protected:
	class CSpriteComponent* sprite = nullptr;


	void Movement(float deltaTime);

	Vector3 CollisionAvoidance();

	bool CanSee(Vector3 posOfObject);

	STATE currentState;

	//BehaviourTree behaviourTree;

	Vector3 velocity;
	Vector3 acceleration;
	Vector3 heading;
	Vector3 aiPosition;

	std::vector<CTile*> tiles;
	std::vector<CTile*> obstacles;

	std::vector<PatrolNode*> patrolNodes;
	std::vector<WaypointNode*> waypointNodes;
	void SetPatrolNodes(std::vector<PatrolNode*> nodes, std::vector<CTile*> waypoints);
	PatrolNode* currentPatrolNode;

	PatrolNode* FindClosestPatrolNode();

	void StateMachine(float deltaTime);
	void Patrolling();
	void SearchForPlayer();
	virtual void ChasePlayer(testCharacter* player);
	virtual void AttackPlayer(testCharacter* player);
	virtual void GetIntoCover() {};

	Vector3 Seek(Vector3 TargetPos);

	void SetPath(WaypointNode* goalWaypoint);
	void CalculatePath(WaypointNode* start, WaypointNode* goal);
	float CalculateCost(WaypointNode* from, WaypointNode* to);
	void ResetNodes();
	void DeleteNodes();
	
	std::vector<WaypointNode*> open;
	std::vector<WaypointNode*> closed;

	// Array of nodes on the path from goal to start.
	std::vector<WaypointNode*> pathNodes;
	int currentCount;

	testCharacter* playerToKill = nullptr;
	testCharacter* playerToChase = nullptr;
	std::vector<testCharacter*> players = Engine::GetEntityOfType<testCharacter>();
	CAICharacter* viewFrustrum = Engine::CreateEntity<CAICharacter>();
	class CSpriteComponent* viewSprite = nullptr;

	float aiHealth = 2.0f;
	float aiSpeed = 100.0f;
	float aiMass = 10.0f;
	float aiRange = 400.0f;
	float aiViewAngle = 45.0f;

	float width = 128.0f;
	float height = 128.0f;

	float rotationSpeed = 0.01f;
	float maxSearchTime = 5.0f;

	float searchTimer = 0.0f;

	float sizeOfTiles = 0.0f;

	
};

