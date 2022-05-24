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
	XMFLOAT2 anchor = { 0.5,0.5 };
	XMUINT2 lastResolution = { 0,0 };

	class CEntity* parent = nullptr;

	bool translucency = false;

	bool ui = false;

	bool shouldUpdate = true;
	bool shouldDraw = false;

	std::string name = "UNNAMED COMPONENT";

public:
	/**
	 * Sets the region of the screen a UI element will be "anchored" to.
	 * {0,0} - top left, {1,1} - bottom right.
	 * Used for making UI elements stick to the edge of the screen when the window is resized.
	 */
	void SetAnchor(const XMFLOAT2& newAnchor) { anchor = newAnchor; updateTransform = true; }

	/**
	 * Sets if this component will/can draw translucent pixels.
	 * THIS FUNCTION IS COSTLY - do NOT micro-manage!
	 * Use this function once per component and leave it.
	 * Will either put the component into the opaque unsorted draw or translucent sorted draw.
	 * Translucent components have a much higher overhead than opaque components.
	 */
	virtual void SetUseTranslucency(const bool& newTranslucency);

	/**
	 * Sets if this component will be drawn in world space or screen space.
	 */
	void SetIsUI(const bool& newIsUI) { ui = newIsUI; }

	/**
	 * Sets if this component will be automatically updated via the Update().
	 */
	void SetShouldUpdate(const bool& newShouldUpdate) { shouldUpdate = newShouldUpdate; }

	/**
	 * Sets if this component will be automatically drawn via the Draw().
	 */
	void SetShouldDraw(const bool& newShouldDraw) { shouldDraw = newShouldDraw; }

	/**
	 * Sets the last resolution variable of the screen for rendering uses.
	 */
	void SetLastResolution(const XMUINT2& newLastResolution) { lastResolution = newLastResolution; }

	/**
	 * Set the parent entity of this component, done automatically.
	 */
	void SetParent(class CEntity* newParent);

	/**
	 * Sets the name of the component mostly for debugging purposes.
	 */
	void SetName(const std::string& newName) { name = newName.c_str(); }

	const bool& GetShouldUpdate() const { return shouldUpdate; }
	const bool& GetShouldDraw() const { return shouldDraw; }
	const bool& GetIsUI() const { return ui; }
	const XMUINT2& GetLastResolution() const { return lastResolution; }
	const bool& GetUseTranslucency() const { return translucency; };
	const XMFLOAT2& GetAnchor() const { return anchor; }
	class CEntity* GetParent() const { return parent; };
	const std::string& GetName() const { return name; };

	/**
	 * Get the position of the component in world space rather than in entity space.
	 */
	XMFLOAT3 GetWorldPosition();
	virtual XMFLOAT4X4 GetTransform() override;

	/**
	 * Updated automatically every single frame.
	 */
	virtual void Update(float deltaTime) = 0;

	/**
	 * Almost the same as Update() but to be used for drawing only.
	 */
	virtual void Draw(struct ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) = 0;
	virtual ~CComponent() {};
};