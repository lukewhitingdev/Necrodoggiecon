#pragma once
#include "Cerberus\Core\CEntity.h"
#include <Cerberus/Core/Components/CAudioEmitterComponent.h>
class AudioEmitterEntity :
    public CEntity
{
public:
    AudioEmitterEntity();
    ~AudioEmitterEntity();

    void SetAudio(const std::string& audioPath, float range);
    void PlayAudio(Vector3 position);
    void Stop();
    void PlayAudio(const std::string& audioPath);
    void PlayAudio();
    void Load(const std::string& audioPath, bool ambient);
    bool SetLooping();
    void SetRange(float range);
    void SetAttachedEntity(CEntity* entity) { isAttached = true;  attachedEntity = entity; }
protected:
    CAudioEmitterComponent* audioEmitter;
    CEntity* attachedEntity;
    bool isAttached;
    // Inherited via CEntity
    virtual void Update(float deltaTime) override;
};

