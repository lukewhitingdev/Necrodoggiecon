#pragma once
#include "Cerberus/Core/CComponent.h"
class CRigidBodyComponent : public CComponent
{
public:
	CRigidBodyComponent();
	virtual ~CRigidBodyComponent();

	virtual void Update(float deltaTime);
	virtual void Draw(struct ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) 
	{
		UNREFERENCED_PARAMETER(context);
		UNREFERENCED_PARAMETER(parentMat);
		UNREFERENCED_PARAMETER(cb);
		UNREFERENCED_PARAMETER(constantBuffer);
	};

	void SetVelocity(const Vector3& velo);
	Vector3& GetVelocity();

	void SetAcceleration(const Vector3& accel);
	Vector3& GetAcceleration();

private:
	float damping;
	Vector3 acceleration;
	Vector3 velocity;
};

