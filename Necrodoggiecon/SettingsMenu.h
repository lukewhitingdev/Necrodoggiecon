/*****************************************************************//**
 * \file   SettingsMenu.h
 * \brief  Header for the settings menu
 * 
 * \author Jack B
 * \date   May 2022
 *********************************************************************/
#pragma once
#include "Cerberus/Core/UI/CWidget_Canvas.h"

class SettingsMenu : public CWidget_Canvas
{
    virtual void InitialiseCanvas() override;

public:
    SettingsMenu();
    void CloseSettings();

private:

    void CreateVolumeUI(Vector2 pos, std::string& title, std::function<void()> volumeUp, std::function<void()> volumeDown);

    void MasterVolumeUp();
    void MasterVolumeDown();

    void AmbientVolumeUp();
    void AmbientVolumeDown();

    void SFXVolumeUp();
    void SFXVolumeDown();
};

