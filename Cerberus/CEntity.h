#pragma once

#include "CComponent.h"
#include "Vector3.h"

////Fundimental class of the engine with a world transform and ability to have components
//Use for all gameplay things in the world
class CEntity
{
protected:
	bool updateTransform = true;
	XMFLOAT4X4 world;

	Vector3 position = { 0,0,0 };
	Vector3 scale = { 1,1,1 };
	float rotation = 0;

public:
	bool shouldUpdate = true;

	std::vector<CComponent*> components;
	
	void SetPosition(float x, float y, float z) { position = Vector3(x, y, z); updateTransform = true; }
	void SetScale(float x, float y, float z) { scale = Vector3(x, y, z); updateTransform = true; }

	void SetPosition(Vector3 In) { position = In; updateTransform = true; }
	void SetScale(Vector3 In) { scale = In; updateTransform = true; }

	void SetRotation(float Rot) { rotation = Rot; updateTransform = true; }

	Vector3 GetPosition() { return position; }
	Vector3 GetScale() { return scale; }
	float GetRotation() { return rotation; }

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

	// Removes the specified component.
	void RemoveComponent(CComponent* reference)
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			CComponent* component = components[i];

			if (component == reference)
			{
				components.erase(components.begin() + i);
				delete component;
				return;
			}
		}
	}
};