#pragma once
#include "Game/LevelTransporter.h"
class NecrodoggieconPage :
    public LevelTransporter
{
public:
    NecrodoggieconPage();
    ~NecrodoggieconPage();
    virtual void OnInteract() override;

protected:
    void OnDialogueClose();
};

