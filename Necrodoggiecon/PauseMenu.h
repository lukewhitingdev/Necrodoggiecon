/*****************************************************************//**
 * \file   PauseMenu.h
 * \brief  Header for the pause menu
 * 
 * \author Jack B
 * \date   May 2022
 *********************************************************************/
#pragma once
#include "Cerberus/Core/UI/CWidget_Canvas.h"

class PauseMenu : public CWidget_Canvas
{
    virtual void InitialiseCanvas() override;

    bool isPaused = false;
    bool gameEnded = false;

private:

    bool pausePressedDown = false;

public:
    PauseMenu();

    void PauseGame();
    void ResumeGame();
    void QuitToMenu();
    void QuitToDesktop();
    void OpenSettingsMenu();

    virtual void Update(float deltaTime) override;

};

