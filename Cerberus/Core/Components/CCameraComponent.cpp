#include "CCameraComponent.h"
#include "Cerberus\Core\Utility\CameraManager\CameraManager.h"

CCameraComponent::CCameraComponent() : attachedToParent(false), view(), proj(), zoom(1), prevPos(Vector3(FLT_MAX, FLT_MAX, FLT_MAX)) 
{
	CameraManager::AddCamera(this);

	UpdateView();
	UpdateProj();
}

CCameraComponent::~CCameraComponent()
{
	CameraManager::RemoveCamera(this);
}


/**
 * Updates the camera's view matrix if the position has changed.
 * 
 * \param deltaTime
 */
void CCameraComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (prevPos != ((attachedToParent) ? this->GetParent()->GetPosition() : this->GetPosition()))
	{
		UpdateView();
		prevPos = (attachedToParent) ? this->GetParent()->GetPosition() : this->GetPosition();
	}
}

/**
 * Sets the zoom level of the camera (FOV).
 * 
 * \param level the zoom level you wish for the camera to be.
 */
void CCameraComponent::SetZoomLevel(const float level)
{
	zoom = level;
	UpdateProj();
}

/**
 * Returns the zoom level of the camera.
 * 
 * \return zoom-level of camera.
 */
float CCameraComponent::GetZoomLevel()
{
	return zoom;
}

/**
 * Sets whether the camera is attached to the parent or if it can move on its own.
 * 
 * \param value whether you would like for the camera to be attached to the parent or not.
 */
void CCameraComponent::SetAttachedToParent(const bool value)
{
	attachedToParent = value;
}

/**
 * Returns whether the camera is attached to the parent of if it can move on its own.
 * 
 * \return whether you are attached to your parent or not.
 */
bool CCameraComponent::getAttachedToParent()
{
	return attachedToParent;
}

/**
 * Returns the view matrix of the camera.
 * 
 * \return view-matrix of camera.
 */
XMFLOAT4X4 CCameraComponent::GetViewMatrix()
{
	return view;
}

/**
 * Returns the projection matrix of the camera.
 * 
 * \return projection-matrix of camera.
 */
XMFLOAT4X4 CCameraComponent::GetProjectionMatrix()
{
	return proj;
}

/**
 * Returns the position of the camera's parent entity.
 * 
 * \return cameras' parent entity's position.
 */
Vector3 CCameraComponent::GetPosition()
{
	if(!attachedToParent)
	{
		XMFLOAT4X4 transform = this->GetTransform();
		XMVECTOR pos;
		XMVECTOR null = DirectX::XMVectorSet(0, 0, 0, 1);
		XMFLOAT3 floatPos;

		pos = DirectX::XMVector3Transform(null, DirectX::XMLoadFloat4x4(&transform));
		DirectX::XMStoreFloat3(&floatPos, pos);
		return Vector3(floatPos.x, floatPos.y, floatPos.z);
	}

	return this->GetParent()->GetPosition();
}

/**
 * Updates the view matrix of the camera.
 * 
 */
void CCameraComponent::UpdateView()
{
	// Initialize the view matrix
	XMFLOAT4 pos = DirectX::XMFLOAT4(this->GetPosition().x + 0.001f, this->GetPosition().y + 0.001f, -1, 1);
	XMFLOAT4 at = DirectX::XMFLOAT4(this->GetPosition().x + 0.001f, this->GetPosition().y + 0.001f, 0, 0);
	XMVECTOR Eye = XMLoadFloat4(&pos);
	XMVECTOR At = XMLoadFloat4(&at);
	XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMMATRIX viewMatrix = XMMatrixLookAtLH(Eye, At, Up);
	XMStoreFloat4x4(&view, viewMatrix);
}

/**
 * Updates the projection matrix of the camera.
 * 
 */
void CCameraComponent::UpdateProj()
{
	XMMATRIX projMatrix = XMMatrixOrthographicLH(Engine::windowWidth / zoom, Engine::windowHeight / zoom, -1000.0f, 1000.0f);
	XMStoreFloat4x4(&proj, projMatrix);
}

