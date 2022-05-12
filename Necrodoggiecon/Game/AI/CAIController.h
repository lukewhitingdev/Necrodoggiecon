#pragma once
#include "Cerberus\Core\CEntity.h"
#include "Cerberus\Core\Utility\Vector3.h"
#include "Cerberus\Core\Components\CSpriteComponent.h"
#include "Necrodoggiecon\Game\AI\CAICharacter.h"
#include <iostream>
#include "Necrodoggiecon\Game\CPlayer.h"
#include "Necrodoggiecon\Game\testClass.h"
#include "Cerberus/Core/Utility/EventSystem/EventSystem.h"
#include "Cerberus\Core\Environment/CWorld.h"
#include "CAINode.h"
#include "Necrodoggiecon\Game\PlayerCharacter.h"
#include "Necrodoggiecon\Game\PlayerController.h"
#include "Necrodoggiecon\Game\CCharacter.h"

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
	virtual void ChasePlayer(PlayerCharacter* player);
	virtual void AttackPlayer(PlayerCharacter* player);
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

	PlayerCharacter* playerToKill = nullptr;
	PlayerCharacter* playerToChase = nullptr;
	std::vector<PlayerController*> playersController = Engine::GetEntityOfType<PlayerController>();
	std::vector<PlayerCharacter*> players = Engine::GetEntityOfType<PlayerCharacter>();
	CAICharacter* viewFrustrum = Engine::CreateEntity<CAICharacter>();
	class CSpriteComponent* viewSprite = nullptr;

	float aiHealth = 2.0f;
	float aiSpeed = 100.0f;
	float aiMass = 10.0f;
	float aiRange = 400.0f;
	float aiViewAngle = 45.0f;

	float width = 64.0f;
	float height = 64.0f;

	float rotationSpeed = 0.01f;
	float maxSearchTime = 5.0f;

	float searchTimer = 0.0f;

	float sizeOfTiles = 0.0f;

	
};

