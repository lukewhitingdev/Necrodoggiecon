#pragma once

#include "CComponent.h"
#include "Utility/CollisionManager/Components/Bodies/CollisionComponent.h"
#include "Vector3.h"

////Fundimental class of the engine with a world transform and ability to have components
//Use for all gameplay things in the world
class CEntity
{
protected:
	XMFLOAT4X4 world;
public:
	bool shouldUpdate = true;
	bool shouldCollide = true;

	void SetPosition(float x, float y, float z) {  position = Vector3(x, y, z); }
	void SetScale(float x, float y, float z) {  scale = Vector3(x, y, z); }

	void SetPosition( Vector3 In) {  position = In; }
	void SetScale( Vector3 In) {  scale = In; }

	void SetRotation( float Rot) { rotation = Rot; }

	Vector3 GetPosition() { return position; }
	Vector3 GetScale() { return scale; }
	float GetRotation() { return rotation; }


	std::vector<CComponent*> components;

	//Updated automatically every single frame
	virtual void Update(float deltaTime) = 0;
	virtual ~CEntity();

	//Convert pos, scale and rot to a XMFloat4x4
	virtual XMFLOAT4X4 GetTransform();

	template <class T>
	T* AddComponent()
	{
		CComponent* tmp = new T();
		components.push_back(tmp);
		return dynamic_cast<T*>(tmp);
	}


protected: 
	Vector3 position = { 0,0,0 };
	Vector3 scale = { 1,1,1 };
	float rotation = 0;
};