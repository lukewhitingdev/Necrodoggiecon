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
<<<<<<< HEAD
    bool gameEnded = false;
=======
>>>>>>> parent of e0b123e (Merge pull request #129 from lukewhitingdev/revert-111-UI)

public:
    PauseMenu();

    void PauseGame();
    void ResumeGame();
    void QuitToMenu();
    void QuitToDesktop();
    void OpenSettingsMenu();

    virtual void Update(float deltaTime) override;

};

