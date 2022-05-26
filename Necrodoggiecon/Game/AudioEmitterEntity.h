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
    void SetAudio(const std::string& audioPath, float range, bool ambient);
    void PlayAudio(Vector3 position);
    void Stop();
    void PlayAudio(const std::string& audioPath);
    void PlayAudio(bool shouldLoop);
    void Load(const std::string& audioPath, bool ambient);
    void SetRange(float range);
    void SetAttachedEntity(CEntity* entity) { isAttached = true;  attachedEntity = entity; }
    void SetName(const std::string& name) { audioName = name; };
protected:
    CAudioEmitterComponent* audioEmitter;
    CEntity* attachedEntity;
    bool isAttached;
    std::string audioName;

    // Inherited via CEntity
    virtual void Update(float deltaTime) override;
};

