/*****************************************************************//**
 * \file   MainMenu.h
 * \brief  Header for the main menu
 * 
 * \author jack_
 * \date   May 2022
 *********************************************************************/
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

