#pragma once
#include <iostream>
#include "Cerberus\Core\CEntity.h"
#include "Cerberus\Core\Utility\Vector3.h"
#include "Cerberus\Core\Components\CSpriteComponent.h"
#include "Cerberus/Core/Utility/EventSystem/EventSystem.h"
#include "Cerberus\Core\Environment/CWorld.h"
#include "Cerberus/Core/Engine.h"

#include "Necrodoggiecon\Game\AI\CAICharacter.h"
#include "Necrodoggiecon\Game\CPlayer.h"
#include "Necrodoggiecon\Game\testClass.h"

#include "Necrodoggiecon\Game\AI\CAINode.h"
#include "Necrodoggiecon\Game\AI\State.h"
#include "Necrodoggiecon\Game\AI\Pathfinding.h"
#include "Necrodoggiecon\Game\testCharacter.h"
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

	void Patrolling();
	void SearchForPlayer();
	
	virtual void ChasePlayer(testCharacter* player);
	virtual void AttackPlayer(testCharacter* player);
	virtual void GetIntoCover() {};
	void SetCurrentState(State& state);

	bool CanSee(Vector3 posOfObject);

	void SetPathNodes(std::vector<WaypointNode*> nodes);
	Pathfinding* pathing;
	void SetPath();

protected:
	class CSpriteComponent* sprite = nullptr;


	void Movement(float deltaTime);

	Vector3 CollisionAvoidance();

	//STATE currentState;

	Vector3 velocity;
	Vector3 acceleration;
	Vector3 heading;
	Vector3 aiPosition;

	std::vector<CTile*> tiles;
	std::vector<CTile*> obstacles;

	PatrolNode* currentPatrolNode;
	
	std::vector<WaypointNode*> pathNodes;

	Vector3 Seek(Vector3 TargetPos);

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

	float width = 64.0f;
	float height = 64.0f;

	float rotationSpeed = 0.01f;
	float maxSearchTime = 5.0f;

	float searchTimer = 0.0f;

	float sizeOfTiles = 0.0f;

	
private:
	State* currentState;
};

