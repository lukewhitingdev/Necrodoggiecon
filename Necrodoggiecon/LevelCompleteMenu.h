/*****************************************************************//**
 * \file   LevelCompleteMenu.h
 * \brief  Header for the level complete screen
 * 
 * \author Jack B
 * \date   May 2022
 *********************************************************************/
#pragma once
#include "Cerberus/Core/UI/CWidget_Canvas.h"

class LevelCompleteMenu : public CWidget_Canvas
{
	virtual void InitialiseCanvas() override;

public:
	LevelCompleteMenu();
	void QuitToMenu();
	void QuitToDesktop();
	void NextLevel();
};

