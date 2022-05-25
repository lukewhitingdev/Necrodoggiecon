#pragma once
/*****************************************************************//**
 * \file   CAIController.h
 * \brief  Header file containing all the functions and variables needed to control the AI.
 * 
 * \author Nasser Ksous
 * \date   May 2022
 *********************************************************************/

#include <iostream>
#include "Cerberus\Core\CEntity.h"
#include "Cerberus\Core\Utility\Vector3.h"
#include "Cerberus\Core\Components\CSpriteComponent.h"
#include "Cerberus/Core/Utility/EventSystem/EventSystem.h"
#include "Cerberus/Core/Engine.h"
#include "Cerberus/Core/Utility/Audio/AudioController.h"
#include "Cerberus/Core/Components/CAudioEmitterComponent.h"

#include "Necrodoggiecon/Game/AI/State.h"
#include "Cerberus/Core/AI/Pathfinding.h"
#include "Necrodoggiecon\Game\CCharacter.h"

/**
 * Controller class for the AI.
 */
class CAIController : public CCharacter
{
public:
	CAIController();
	~CAIController();

	void SetRotationSpeed(float speed);
	float GetRotationSpeed();

	void SetSearchTime(float time);
	float GetSearchTime();

	void SetInitialSpeed(float speed);
	float GetInititalSpeed();
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

	void SetPositionToInvestigate(Vector3 pos);
	Vector3 GetPositionToInvestigate();

	void SetIsAttacking(bool isAttack);
	bool GetIsAttacking();

	void SetSpriteSize(float size);
	float GetSpriteSize();

	virtual void Update(float deltaTime) override;

	void Patrolling();
	void SearchForPlayer();
	void Investigating(Vector3 positionOfInterest);
	
	virtual void AttackEnter(CCharacter* player);
	virtual void ChaseEnter();
	virtual void ChasePlayer(CCharacter* player);
	virtual void AttackPlayer(CCharacter* player, float deltaTime);

	void SetCurrentState(State& state);
	bool CanSee(CCharacter* player);

	void SetPathNodes(std::vector<WaypointNode*> nodes);
	Pathfinding* pathing;
	void SetPath();
	void SetPath(Vector3 endPosition);

	void ApplyDamage(float damageAmount);
	void ApplyDamage(float damageAmount, const std::string& hitAudioPath);

	class CAnimationSpriteComponent* sprite = nullptr;

protected:
	virtual void OnHit(const std::string& hitSound) {};
	virtual void OnDeath() {};

	class CSpriteComponent* viewFrustrum = nullptr;

	Vector3 positionToInvestigate;
	void Movement(float deltaTime);

	Vector3 CollisionAvoidance();

	Vector3 velocity;
	Vector3 acceleration;
	Vector3 heading;
	Vector3 aiPosition;

	std::vector<CTile*> tiles;
	std::vector<CTile*> obstacles;

	PatrolNode* currentPatrolNode;
	
	std::vector<WaypointNode*> pathNodes;

	Vector3 Seek(Vector3 TargetPos);

	void CheckForPlayer();

	void MoveViewFrustrum();

	int currentCount;
	bool isAttacking = false;

	CCharacter* playerToKill = nullptr;
	CCharacter* playerToChase = nullptr;
	

	std::vector<CCharacter*> characters = Engine::GetEntityOfType<CCharacter>();
	std::vector<CCharacter*> players;

	float aiSpeed = 100.0f;
	float initialSpeed = aiSpeed;
	float aiMass = 10.0f;
	float aiRange = 200.0f;
	float aiViewAngle = 90.0f;

	float width = 64.0f;
	float height = 64.0f;

	float rotationSpeed = 0.01f;
	float maxSearchTime = 5.0f;

	float searchTimer = 0.0f;

	float sizeOfTiles = 0.0f;

	float spriteSize = 64.0f;

	State* currentState;

	virtual void HasCollided(CollisionComponent* collidedObject)
	{
		if (collidedObject->GetName() == "Wall")
		{
			colComponent->Resolve(collidedObject);
			this->SetPosition(colComponent->GetPosition());
		}
	}
};

