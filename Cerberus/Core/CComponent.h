/*****************************************************************//**
 * \file   CComponent.h
 * \brief  Fundamental component class of the engine.
 * 
 * \author Arrien Bidmead
 * \date   January 2022
 *********************************************************************/

#pragma once
#include "Cerberus\Core\Engine.h"
#include "Cerberus\Core\Utility\Vector3.h"
#include "Cerberus/Core/Utility/CTransform.h"

/**
 * Fundamental component class of the engine.
 * Can be extended upon to make new components to add to CEntity.
 */
class CComponent : public CTransform
{
protected:
	XMFLOAT2 anchor = { 0.5,0.5 };
	XMUINT2 lastResolution = { 0,0 };

	class CEntity* parent = nullptr;

	bool translucency = false;

public:
	bool ui = false;

	bool shouldUpdate = true;
	bool shouldDraw = false;

	/**
	 * Sets the region of the screen a UI element will be "anchored" to.
	 * {0,0} - top left, {1,1} - bottom right.
	 * Used for making UI elements stick to the edge of the screen when the window is resized.
	 */
	void SetAnchor(XMFLOAT2 newAnchor) { anchor = newAnchor; updateTransform = true; }
	void SetParent(class CEntity* newParent);

	/**
	 * Sets if this component will/can draw translucent pixels.
	 * THIS FUNCTION IS COSTLY - do NOT micro-manage!
	 * Use this function once per component and leave it.
	 * Will either put the component into the opaque unsorted draw or translucent sorted draw.
	 * Translucent components have a much higher overhead than opaque components.
	 */
	virtual void SetUseTranslucency(const bool& newTranslucency);
	const bool& GetUseTranslucency() const { return translucency; };

	const XMFLOAT2& GetAnchor() const { return anchor; }
	class CEntity* GetParent() const { return parent; };

	/**
	 * Updated automatically every single frame.
	 */
	virtual void Update(float deltaTime) = 0;

	/**
	 * Almost the same as Update() but to be used for drawing only.
	 */
	virtual void Draw(struct ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) = 0;
	virtual ~CComponent() {};

	/**
	 * Get the position of the component in world space rather than in entity space.
	 */
	XMFLOAT3 GetWorldPosition();

	virtual XMFLOAT4X4 GetTransform() override;
};