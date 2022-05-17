#pragma once
#include "Cerberus/Core/UI/CWidget.h"

class CWidget_Button :
    public CWidget
{
public:

    CWidget_Button();
    class CSpriteComponent* sprite = nullptr;

    void SetSlot(int Slot) { buttonSlot = Slot; }
    void SetText(std::string TextBody);
    void SetSize(Vector2 Size);


    virtual void OnButtonPressed();
    virtual void OnButtonReleased();

    virtual void OnButtonHoverStart();
    virtual void OnButtonHoverEnd();


    void IsButtonFocused(Vector2 mPos);
    void ButtonTriggered();


private: 

   
    int buttonSlot;
    bool hasFocus;

    class CWidget_Canvas* OwningCanvas;

    

    



};

