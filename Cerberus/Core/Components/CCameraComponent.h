

#pragma once
#include <DirectXMath.h>
#include "Cerberus/Core/CComponent.h"
#include "Cerberus/Core/CEntity.h"
class CCameraComponent : public CComponent
{
public:
	CCameraComponent();
	virtual ~CCameraComponent() {};

	void Initialize();

	virtual void Update(float deltaTime) override;
	virtual void Draw(struct ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) override {};

	void SetZoomLevel(const float level);
	float GetZoomLevel();

	XMFLOAT4X4 GetViewMatrix();
	XMFLOAT4X4 GetProjectionMatrix();

	void SetPosition(Vector3 pos) { this->GetParent()->SetPosition(pos); };
	Vector3 GetPosition();

private:
	void UpdateView();
	void UpdateProj();

	XMFLOAT4X4 view;
	XMFLOAT4X4 proj;
	float zoom = 1;

	Vector3 prevPos;
};

