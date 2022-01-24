#include "CAudioListenerComponent.h"

CAudioListenerComponent::CAudioListenerComponent()
{
	shouldUpdate = true;
	shouldDraw = false;
	ui = false;

	fmodPosition = new FMOD_VECTOR();
	fmodPreviousPosition = new FMOD_VECTOR();
	fmodVelocity = new FMOD_VECTOR();

	fmodForward = new FMOD_VECTOR();
	fmodForward->y = 1;
	fmodUp = new FMOD_VECTOR();
	fmodUp->z = 1;
}

CAudioListenerComponent::~CAudioListenerComponent()
{
	delete fmodPosition;
	delete fmodPreviousPosition;
}

void CAudioListenerComponent::Update(float deltaTime)
{
	FMOD_RESULT result;

	if (fmodPosition != nullptr && fmodVelocity != nullptr && fmodPreviousPosition != nullptr)
	{
		// Set Position to new updated position
		fmodPosition->x = this->GetPosition().x;
		fmodPosition->y = this->GetPosition().y;
		fmodPosition->z = this->GetPosition().z;

		// Calculate Velocity. (Difference from previous frame) * 1000 / time passed between frames.
		fmodVelocity->x = (fmodPosition->x - fmodPreviousPosition->x) * 1000 / deltaTime;
		fmodVelocity->y = (fmodPosition->y - fmodPreviousPosition->y) * 1000 / deltaTime;
		fmodVelocity->z = (fmodPosition->z - fmodPreviousPosition->z) * 1000 / deltaTime;

		Debug::Log("Listener Location: x:%f(%f), y:%f(%f), z:%f(%f)",
			fmodPosition->x, fmodVelocity->x,
			fmodPosition->y, fmodVelocity->y,
			fmodPosition->z, fmodVelocity->z);

		// Set Previous Position up for the next call.
		fmodPreviousPosition = fmodPosition;

		// Set 3D Attributes
		if ((result = AudioController::getSystem()->set3DListenerAttributes(0, fmodPosition, fmodVelocity, fmodForward, fmodUp)) != FMOD_OK)
		{
			Debug::LogError("[Listener Component Update] FMOD Error[%d]: %s ", result, FMOD_ErrorString(result));
			return;
		}

		if ((result = AudioController::getSystem()->update()) != FMOD_OK)
		{
			Debug::LogError("[Listener Component Update] FMOD Error[%d]: %s ", result, FMOD_ErrorString(result));
			return;
		}
	}
}
