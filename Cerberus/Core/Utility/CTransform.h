/*****************************************************************//**
 * \file   CTransform.h
 * \brief  A transform class that contains getters and setters.
 * 
 * \author Arrien Bidmead
 * \date   January 2022
 *********************************************************************/

#pragma once
#include "Cerberus\Core\Engine.h"
#include "Cerberus\Core\Utility\Vector3.h"

/**
 * A transform class that contains getters and setters.
 */
class CTransform
{
	Vector3 position = { 0,0,0 };
	Vector3 scale = { 1,1,1 };
	float rotation = 0;

protected:
	bool updateTransform = true;	//use get transform instead of directly using this
	XMFLOAT4X4 world = XMFLOAT4X4();

public:
	void SetPosition(const float& x, const float& y, const float& z) { position = Vector3(x, y, z); updateTransform = true; }
	void SetScale(const float& x, const float& y, const float& z) { scale = Vector3(x, y, z); updateTransform = true; }

	void SetPosition(const Vector3& In) { position = In; updateTransform = true; }
	void SetScale(const Vector3& In) { scale = In; updateTransform = true; }

	void SetRotation(const float& Rot);

	const Vector3& GetPosition() const { return position; }
	const Vector3& GetScale() const { return scale; }
	const float& GetRotation() const { return rotation; }

	//Convert pos, scale and rot to a XMFloat4x4
	virtual XMFLOAT4X4 GetTransform();
};
