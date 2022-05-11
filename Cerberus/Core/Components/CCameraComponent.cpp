#include "CCameraComponent.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"

CCameraComponent::CCameraComponent() : view(), proj(), zoom(1), prevPos(Vector3(FLT_MAX, FLT_MAX, FLT_MAX)) {}

void CCameraComponent::Update(float deltaTime)
{
	if (prevPos != this->GetParent()->GetPosition())
	{
		UpdateView();
		prevPos = this->GetParent()->GetPosition();
	}
}

void CCameraComponent::Initialize()
{
	UpdateView();
	UpdateProj();
}


void CCameraComponent::SetZoomLevel(const float level)
{
	zoom = level;
	UpdateProj();
}

float CCameraComponent::GetZoomLevel()
{
	return zoom;
}

XMFLOAT4X4 CCameraComponent::GetViewMatrix()
{
	return view;
}

XMFLOAT4X4 CCameraComponent::GetProjectionMatrix()
{
	return proj;
}

Vector3 CCameraComponent::GetPosition()
{
	return this->GetParent()->GetPosition();
}

void CCameraComponent::UpdateView()
{
	// Initialize the view matrix
	XMFLOAT4 pos = DirectX::XMFLOAT4(this->GetParent()->GetPosition().x + 0.001f, this->GetParent()->GetPosition().y + 0.001f, this->GetParent()->GetPosition().z + 0.001f, 1);
	XMFLOAT4 at = DirectX::XMFLOAT4(this->GetParent()->GetPosition().x + 0.001f, this->GetParent()->GetPosition().y + 0.001f, 0, 0);
	XMVECTOR Eye = XMLoadFloat4(&pos);
	XMVECTOR At = XMLoadFloat4(&at);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX viewMatrix = XMMatrixLookAtLH(Eye, At, Up);
	XMStoreFloat4x4(&view, viewMatrix);
}

void CCameraComponent::UpdateProj()
{
	// Initialize the projection matrix
	XMMATRIX projMatrix = XMMatrixOrthographicLH(Engine::windowWidth / zoom, Engine::windowHeight / zoom, 0.01f, 100.0f);
	XMStoreFloat4x4(&proj, projMatrix);
}

