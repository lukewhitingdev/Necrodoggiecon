#pragma once
#include "Cerberus/Core/UI/CWidget_Canvas.h"
class MainMenu :
    public CWidget_Canvas
{


    virtual void InitialiseCanvas() override;


public:
    MainMenu();

    void QuitToDesktop();

    void OpenLevelSelect();
    void OpenSettingsMenu();

};

