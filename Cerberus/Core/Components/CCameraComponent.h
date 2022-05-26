/*****************************************************************//**
 * \file   CCameraComponent.h
 * \brief  Used to attach a camera to a entity.
 * 
 * \author Luke Whiting
 * \date   May 2022
 *********************************************************************/

#pragma once
#include <DirectXMath.h>
#include "Cerberus/Core/CComponent.h"
#include "Cerberus/Core/CEntity.h"
class CCameraComponent : public CComponent
{
public:
	CCameraComponent();
	virtual ~CCameraComponent();

	virtual void Update(float deltaTime) override;
	virtual void Draw(struct ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) override {UNREFERENCED_PARAMETER(context); UNREFERENCED_PARAMETER(parentMat); UNREFERENCED_PARAMETER(cb); UNREFERENCED_PARAMETER(constantBuffer);};

	void SetZoomLevel(const float level);
	float GetZoomLevel();

	void SetAttachedToParent(const bool value);
	bool getAttachedToParent();

	XMFLOAT4X4 GetViewMatrix();
	XMFLOAT4X4 GetProjectionMatrix();

	Vector3 GetPosition();

	void UpdateView();
	void UpdateProj();
private:

	bool attachedToParent;

	XMFLOAT4X4 view;
	XMFLOAT4X4 proj;
	float zoom = 1;

	Vector3 prevPos;
};

