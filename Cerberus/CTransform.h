#pragma once
#include "Engine.h"
#include "Vector3.h"

class CTransform
{
	Vector3 position = { 0,0,0 };
	Vector3 scale = { 1,1,1 };
	float rotation = 0;

protected:
	bool updateTransform = true;	//use get transform instead of directly using this
	XMFLOAT4X4 world;

public:
	void SetPosition(float x, float y, float z) { position = Vector3(x, y, z); updateTransform = true; }
	void SetScale(float x, float y, float z) { scale = Vector3(x, y, z); updateTransform = true; }

	void SetPosition(Vector3 In) { position = In; updateTransform = true; }
	void SetScale(Vector3 In) { scale = In; updateTransform = true; }

	void SetRotation(float Rot) { rotation = Rot; updateTransform = true; }

	const Vector3& GetPosition() const { return position; }
	const Vector3& GetScale() const { return scale; }
	const float& GetRotation() const { return rotation; }

	//Convert pos, scale and rot to a XMFloat4x4
	virtual XMFLOAT4X4 GetTransform();
};
