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

    virtual void Update(float deltaTime) override;

private:

    CWidget_Text* CreateVolumeUI(Vector2 pos, const std::string& title, const int& volume, std::function<void()> volumeUp, std::function<void()> volumeDown);

    void MasterVolumeUp();
    void MasterVolumeDown();

    CWidget_Text* masterVolumeText = nullptr;

    int masterVolume = 100;
};

