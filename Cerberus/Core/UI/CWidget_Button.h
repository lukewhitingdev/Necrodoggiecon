#pragma once
#include "Cerberus/Core/UI/CWidget.h"
#include <functional>

class CWidget_Button :
    public CWidget
{
public:

    CWidget_Button();
   

    void SetSlot(int Slot) { buttonSlot = Slot; }
    void SetText(std::string TextBody);
    void SetButtonSize(Vector2 Size);
    void SetTexture(std::string filePath);

    virtual void SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder);
    

    virtual void Update(float deltaTime) override;


    virtual void OnButtonPressed();
    virtual void OnButtonReleased();

    virtual void OnButtonHoverStart();
    virtual void OnButtonHoverEnd();


    virtual void SetVisibility(bool IsVisible);

    void IsButtonFocused(Vector2 mPos);
    void ButtonPressed(bool buttonPressed);

    void Bind_OnButtonPressed(std::function<void()> functionToBind) { ButtonPressedBind = functionToBind; }
    void Bind_OnButtonReleased(std::function<void()> functionToBind) { ButtonReleasedBind = functionToBind; }
    void Bind_HoverStart(std::function<void()> functionToBind) { HoverStartBind = functionToBind; }
    void Bind_HoverEnd(std::function<void()> functionToBind) { ButtonReleasedBind = functionToBind; }

    class CSpriteComponent* GetSprite() { return sprite; }
    class CTextRenderComponent* GetText() { return textRenderer; }

    bool ButtonHasFocus() { return hasFocus; }


private: 

    Vector2 SpriteSize;

    std::function<void()> HoverStartBind;
    std::function<void()> HoverEndBind;

    std::function<void()> ButtonPressedBind;
    std::function<void()> ButtonReleasedBind;

   
    int buttonSlot;
    bool hasFocus;
   
    class CWidget_Canvas* OwningCanvas;

    class CSpriteComponent* sprite = nullptr;
    class CTextRenderComponent* textRenderer = nullptr;

    

    



};

