#pragma once
#include "CComponent.h"
#include "Utility/Audio/AudioController.h"
#include "Utility/DebugOutput/Debug.h"

//Fundimental component class
//Can be extended upon to make new components to add to CEntity
class CAudioEmitterComponent : public CComponent
{
public:
	CAudioEmitterComponent();
	~CAudioEmitterComponent();
	void Load(std::string path);
	void Play();
	void Stop();
	void SetRange(float range);

	//Updated automatically every single frame
	virtual void Update(float deltaTime);

	virtual void Draw(struct ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer)
	{
		UNREFERENCED_PARAMETER(context);
		UNREFERENCED_PARAMETER(parentMat);
		UNREFERENCED_PARAMETER(cb);
		UNREFERENCED_PARAMETER(constantBuffer);
	};

private:
	CEmitter* emitter;
};