/*****************************************************************//**
 * \file   CCamera.h
 * \brief  Class for storing all camera information needed for rendering.
 * 
 * \author Arrien Bidmead
 * \date   January 2022
 *********************************************************************/

#pragma once
#include "Cerberus\Core\Engine.h"

/**
 * Class for storing all camera information needed for rendering.
 */
class CCamera
{
	XMFLOAT4 eyePosition = { 0,0,-3,1 };
	float zoom = 1;

public:
	XMFLOAT4X4 view;
	XMFLOAT4X4 proj;

	void UpdateViewMat();
	void UpdateProjectionMat();

	CCamera();
	void SetCameraPosition(XMFLOAT4 newPos) { eyePosition = newPos; UpdateViewMat(); }
	const XMFLOAT4& GetCameraPosition() const { return eyePosition; }

	void SetZoom(float newZoom) { zoom = newZoom; UpdateProjectionMat(); }
	const float& GetZoom() const { return zoom; }
};
