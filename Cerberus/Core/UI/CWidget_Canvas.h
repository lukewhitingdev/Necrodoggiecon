#pragma once
#include "Cerberus/Core/UI/CWidget.h"
class CWidget_Canvas :
    public CWidget
{


public:

    CWidget_Canvas();

    virtual void InitialiseCanvas();

    virtual void Update(float deltaTime) override;

    Vector2 GetMousePosition();

    virtual void RecievedUIEvent(int EventID);

    void CreateButton(Vector2 Position, Vector2 Scale, std::string ButtonName, int ID);

protected: 

    std::vector<class CWidget_Button*> buttonList;
    
    
};

