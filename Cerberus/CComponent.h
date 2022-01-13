#pragma once
#include "Engine.h"

//Fundimental component class
//Can be extended upon to make new components to add to CEntity
class CComponent
{
protected:
	XMFLOAT4X4 world;
public:
	bool shouldUpdate = true;
	XMFLOAT3 position = { 0,0,0 };
	XMFLOAT3 scale = { 1,1,1 };
	float rotation = 0;
	bool shouldDraw = false;
public:
	//Updated automatically every single frame
	virtual void Update(float deltaTime) = 0;
	//Almost the same as Update() but to be used for drawing only.
	virtual void Draw(struct ID3D11DeviceContext* context) = 0;
	virtual ~CComponent() {};

	//Convert pos, scale and rot to a XMFloat4x4
	virtual XMFLOAT4X4 GetTransform();
};