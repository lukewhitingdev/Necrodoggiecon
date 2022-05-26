/*****************************************************************//**
 * \file   CAudioEmitterComponent.h
 * \brief  Allows a entity to emit audio.
 *
 * \author Luke Whiting
 * \date   Jan 2021
 *********************************************************************/
#pragma once
#include "Cerberus\Core\CComponent.h"
#include "Cerberus/Core/Utility/Audio/AudioController.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"

//Fundimental component class
//Can be extended upon to make new components to add to CEntity
class CAudioEmitterComponent : public CComponent
{
public:
	CAudioEmitterComponent();
	~CAudioEmitterComponent();
	void Load(const std::string& path);
	void Load(const std::string& path, bool ambient);
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