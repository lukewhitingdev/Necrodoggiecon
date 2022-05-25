#pragma once
#include "Cerberus\Core\CEntity.h"
#include <Cerberus/Core/Components/CAudioEmitterComponent.h>
class AudioEmitterEntity :
    public CEntity
{
public:
    AudioEmitterEntity();
    ~AudioEmitterEntity();

    void SetAudio(const std::string audioPath, float range);
    void PlayAudio(Vector3 position);
protected:
    CAudioEmitterComponent* audioEmitter;

    // Inherited via CEntity
    virtual void Update(float deltaTime) override;
};

