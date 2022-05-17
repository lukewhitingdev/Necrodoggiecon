#pragma once
#include "Cerberus/Core/UI/CWidget.h"
class CWidget_Canvas :
    public CWidget
{


public:

    CWidget_Canvas();

    virtual void InitialiseCanvas();

    virtual void Update(float deltaTime) override;
};

