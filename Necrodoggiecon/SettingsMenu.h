#pragma once
#include "Cerberus/Core/UI/CWidget_Canvas.h"

class SettingsMenu : public CWidget_Canvas
{
    virtual void InitialiseCanvas() override;

public:
    SettingsMenu();
    void CloseSettings();
};

