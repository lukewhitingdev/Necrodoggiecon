#pragma once
#include "Cerberus/Core/UI/CWidget.h"

class CWidget_Button :
    public CWidget
{
public:

    CWidget_Button();
    class CSpriteComponent* sprite = nullptr;


    void SetText(std::string TextBody);
    void SetSize(Vector2 Size);


    virtual void OnButtonPressed();
    virtual void OnButtonReleased();

    virtual void OnButtonHoverStart();
    virtual void OnButtonHoverEnd();

    

    



};

