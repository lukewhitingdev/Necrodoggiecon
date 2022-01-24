#pragma once
#include "CComponent.h"
#include "Utility/Audio/AudioController.h"

//Fundimental component class
//Can be extended upon to make new components to add to CEntity
class CAudioListenerComponent : public CComponent
{
public:
	CAudioListenerComponent();
	~CAudioListenerComponent();

	//Updated automatically every single frame
	virtual void Update(float deltaTime);

	virtual void Draw(struct ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) {};

private:

	FMOD_VECTOR* fmodPosition;
	FMOD_VECTOR* fmodPreviousPosition;
	FMOD_VECTOR* fmodVelocity;
	FMOD_VECTOR* fmodForward;
	FMOD_VECTOR* fmodUp;
};