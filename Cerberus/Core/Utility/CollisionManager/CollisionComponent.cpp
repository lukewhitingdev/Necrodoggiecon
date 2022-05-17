#include "CollisionComponent.h"
#include "Cerberus\Core\CEntity.h"
#include <Cerberus/Core/Components/CRigidBodyComponent.h>


CollisionComponent::CollisionComponent(std::string setName, CEntity* owner)
{
	collisionType = COLLISIONTYPE::BOUNDING_NONE;
	parent = owner;
	name = setName;
};

CollisionComponent::~CollisionComponent()
{

}

COLLISIONTYPE CollisionComponent::GetCollisionType()
{
	return collisionType;
}

float CollisionComponent::GetRadius()
{
	return radius;
}

void CollisionComponent::SetRadius(float setRadius)
{
	radius = setRadius;
}

void CollisionComponent::SetPosition(Vector3 setPosition)
{
	position = setPosition;
}

Vector3 CollisionComponent::GetPosition()
{
	return position;
}

/**
 * Resolves collisions between two collider's.
 * 
 * \param other
 */
void CollisionComponent::Resolve(CollisionComponent* other)
{
	// Dont resolve if we are a wall, walls dont move.... yet.
	if (this->GetName() == "Wall")
		return;

	Vector3 out = this->GetPosition();

	if(this->collisionType == COLLISIONTYPE::BOUNDING_BOX && other->collisionType == COLLISIONTYPE::BOUNDING_BOX)
	{
		Vector3 toThis = other->GetPosition() - this->GetPosition();

		float intersectDepthRight = (this->GetPosition().x + this->GetWidth() / 2) - (other->GetPosition().x - other->GetWidth() / 2);
		float intersectDepthLeft = (this->GetPosition().x - this->GetWidth() / 2) - (other->GetPosition().x + other->GetWidth() / 2);

		float intersectDepthTop = (this->GetPosition().y + this->GetWidth() / 2) - (other->GetPosition().y - other->GetWidth() / 2);
		float intersectDepthBottom = (this->GetPosition().y - this->GetWidth() / 2) - (other->GetPosition().y + other->GetWidth() / 2);


		if (abs(toThis.x) > abs(toThis.y))
		{
			if (this->GetPosition().x < other->GetPosition().x)
			{
				// Right.
				out.x -= intersectDepthRight;
			}
			else
			{
				// Left.
				out.x -= intersectDepthLeft;
			}
		}
		else if (abs(toThis.y) > abs(toThis.x))
		{
			if (this->GetPosition().y < other->GetPosition().y)
			{
				// Up.
				out.y -= intersectDepthTop;
			}
			else
			{
				// Down.
				out.y -= intersectDepthBottom;
			}
		}
	}
	else if(this->GetCollisionType() == COLLISIONTYPE::BOUNDING_CIRCLE && other->GetCollisionType() == COLLISIONTYPE::BOUNDING_CIRCLE)
	{
		float ang = atan2f(other->GetPosition().y - this->GetPosition().y, other->GetPosition().x - this->GetPosition().x);
		float dist = this->GetPosition().DistanceTo(other->GetPosition());
		float resolveDist = this->GetRadius() + other->GetRadius() - dist;
		out.x -= cos(ang) * resolveDist;
		out.y -= sin(ang) * resolveDist;
	}

	this->SetPosition(out);
}

void CollisionComponent::SetTrigger(bool value)
{
	trigger = value;
}

bool CollisionComponent::GetTrigger()
{
	return trigger;
}

//Checks if a circle has intersected with a box
bool CollisionComponent::Intersects(CollisionComponent* circle, CollisionComponent* box)
{
	float distance = DistanceBetweenPoints(box->position, circle->position);

	if (distance > (box->width) + circle->radius || distance > (box->height) + circle->radius)
		return false;

	if (distance <= box->width || distance <= box->height)
		return true;

	return false;
}

//SetCollider overload for bounding circle
void CollisionComponent::SetCollider(float setRadius)
{
	collisionType = COLLISIONTYPE::BOUNDING_CIRCLE;
	radius = setRadius;
}
//SetCollider overload for bounding box
void CollisionComponent::SetCollider(float setHeight, float setWidth)
{
	collisionType = COLLISIONTYPE::BOUNDING_BOX;
	height = setHeight;
	width = setWidth;
}

bool CollisionComponent::IsColliding(CollisionComponent* collidingObject)
{
	if (collisionType == COLLISIONTYPE::BOUNDING_CIRCLE)
	{
		switch (collidingObject->GetCollisionType())
		{
			case COLLISIONTYPE::BOUNDING_CIRCLE:
			{
				Vector3 otherPos = collidingObject->GetPosition();
				Vector3 thisPos = position;
				otherPos.z = 0;
				thisPos.z = 0;
				if (DistanceBetweenPoints(thisPos, otherPos) < (radius + (collidingObject)->radius))
				{
					return true;
				}
				break;
			}
			case COLLISIONTYPE::BOUNDING_BOX:
			{
				if (Intersects(this, collidingObject))
				{
					return true;
				}
				break;
			}
		}

	}
	else if (collisionType == COLLISIONTYPE::BOUNDING_BOX)
	{
		switch (collidingObject->GetCollisionType())
		{
			case COLLISIONTYPE::BOUNDING_CIRCLE:
			{
				if (Intersects(collidingObject, this))
				{
					return true;
				}
				break;
			}
			case COLLISIONTYPE::BOUNDING_BOX:
			{
				Vector3 otherPos = collidingObject->GetPosition();
				Vector3 thisPos = position;
				otherPos.z = 0;
				thisPos.z = 0;

				if (thisPos.x - (width / 2) <= otherPos.x + (collidingObject->GetWidth() / 2) && 
					thisPos.x + (width / 2) >= otherPos.x - (collidingObject->GetWidth() / 2) &&
					thisPos.y - (height / 2) <= otherPos.y + (collidingObject->GetHeight() / 2) && 
					thisPos.y + (height / 2) >= otherPos.y - (collidingObject->GetHeight() / 2))
				{
					return true;
				}
				break;
			}
		}
	}
	return false;
}

float CollisionComponent::DistanceBetweenPoints(Vector3& point1, Vector3& point2)
{
	float distance = sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y) + (point1.z - point2.z) * (point1.z - point2.z));
	return distance;
}

CEntity* CollisionComponent::GetParent()
{
	return parent;
};
