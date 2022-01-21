#pragma once
#include "CT_WindowBase.h"
class CT_Window_ToolBar : public CT_WindowBase
{
public:
	CT_Window_ToolBar();

protected:
	virtual void    AdditionalRenderLogic(bool& isOpen) override;
};

