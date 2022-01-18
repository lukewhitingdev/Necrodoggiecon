#include "CCamera.h"

CCamera::CCamera()
{
	UpdateViewMat();
	UpdateProjectionMat();
}

void CCamera::UpdateViewMat()
{
	// Initialize the view matrix
	XMVECTOR Eye = XMLoadFloat4(&eyePosition);
	XMVECTOR At = XMVectorSet(eyePosition.x, eyePosition.y, 0, 0);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX viewMatrix = XMMatrixLookAtLH(Eye, At, Up);
	XMStoreFloat4x4(&view, viewMatrix);
}

void CCamera::UpdateProjectionMat()
{
	// Initialize the projection matrix
	XMMATRIX projMatrix = XMMatrixOrthographicLH(Engine::windowWidth / zoom, Engine::windowHeight / zoom, 0.01f, 100.0f);
	XMStoreFloat4x4(&proj, projMatrix);
}
