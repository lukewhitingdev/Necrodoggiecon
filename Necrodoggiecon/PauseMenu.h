#pragma once
#include "Cerberus/Core/UI/CWidget_Canvas.h"

class PauseMenu : public CWidget_Canvas
{
    virtual void InitialiseCanvas() override;

    bool isPaused = false;

public:
    PauseMenu();

    void PauseGame();
    void ResumeGame();
    void QuitToMenu();
    void QuitToDesktop();

    virtual void Update(float deltaTime) override;

};

