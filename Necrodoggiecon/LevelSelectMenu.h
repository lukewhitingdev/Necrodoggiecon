#pragma once
#include "Cerberus/Core/UI/CWidget_Canvas.h"

class LevelSelectMenu : public CWidget_Canvas
{
    virtual void InitialiseCanvas() override;

    int SelectedLevel = 0;

    CWidget_Button* LVL0;
    CWidget_Button* LVL1;
    CWidget_Button* LVL2;
    CWidget_Button* LVL3;
    CWidget_Button* LVL4;
    CWidget_Button* LVL5;
    CWidget_Button* LVL6;
    CWidget_Button* LVL7;

public:
    LevelSelectMenu();
    void CloseMenu();

    void OpenLevelTutorial();
    void OpenLevel1();
    void OpenLevel2();
    void OpenLevel3();
    void OpenLevel4();
    void OpenLevel5();
    void OpenLevel6();
    void OpenLevel7();

    void UpdateButtonPositions();

    void PlayLevel();

};

