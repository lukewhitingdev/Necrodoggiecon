#pragma once
#include "Engine.h"

class CCamera
{
	XMFLOAT4 eyePosition = { 0,0,-3,1 };

public:
	XMFLOAT4X4 view;
	XMFLOAT4X4 proj;
	float zoom = 1;

	void UpdateViewMat();
	void UpdateProjectionMat();

	CCamera();
	void SetCameraPosition(XMFLOAT4 newPos) { eyePosition = newPos; UpdateViewMat(); }
	XMFLOAT4 GetCameraPosition() { return eyePosition; }
};
