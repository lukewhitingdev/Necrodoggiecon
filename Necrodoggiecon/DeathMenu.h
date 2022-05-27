#pragma once
#include "Cerberus/Core/UI/CWidget_Canvas.h"
class DeathMenu : public CWidget_Canvas
{
	virtual void InitialiseCanvas() override;

public:
	DeathMenu();
	void QuitToMenu();
	void QuitToDesktop();
	void restartLevel();
};

