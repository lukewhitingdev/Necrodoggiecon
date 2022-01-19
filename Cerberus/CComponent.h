#pragma once
#include "Engine.h"
#include "Vector3.h"

//Fundimental component class
//Can be extended upon to make new components to add to CEntity
class CComponent
{
protected:
	bool updateTransform = true;
	XMFLOAT4X4 world = XMFLOAT4X4();

	Vector3 position = { 0,0,0 };
	Vector3 scale = { 1,1,1 };
	float rotation = 0;

public:
	bool shouldUpdate = true;
	bool shouldDraw = false;

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
	//Almost the same as Update() but to be used for drawing only.
	virtual void Draw(struct ID3D11DeviceContext* context) = 0;
	virtual ~CComponent() {};

	//Convert pos, scale and rot to a XMFloat4x4
	virtual XMFLOAT4X4 GetTransform();
};