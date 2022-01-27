#pragma once
#include "Engine.h"
#include "Vector3.h"
#include "CTransform.h"

//Fundimental component class
//Can be extended upon to make new components to add to CEntity
class CComponent : public CTransform
{
protected:
	XMFLOAT2 anchor = { 0.5,0.5 };
	XMFLOAT2 lastResolution = { 0,0 };

	class CEntity* parent = nullptr;

public:
	bool ui = false;

	bool shouldUpdate = true;
	bool shouldDraw = false;

	//Sets the region of the screen a UI element will be "anchored" to.
	//{0,0} - top left, {1,1} - bottom right.
	//Used for making UI elements stick to the edge of the screen when the window is resized
	void SetAnchor(XMFLOAT2 newAnchor) { anchor = newAnchor; updateTransform = true; }
	void SetParent(class CEntity* newParent);

	const XMFLOAT2& GetAnchor() const { return anchor; }
	class CEntity* GetParent() const { return parent; };

	//Updated automatically every single frame
	virtual void Update(float deltaTime) = 0;
	//Almost the same as Update() but to be used for drawing only.
	virtual void Draw(struct ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) = 0;
	virtual ~CComponent() {};

	virtual XMFLOAT4X4 GetTransform() override;
};