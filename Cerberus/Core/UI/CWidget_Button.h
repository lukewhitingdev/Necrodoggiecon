/*****************************************************************//**
 * \file   CWidget_Button.cpp
 * \brief  Button Widget class, provides all functionality for buttons and allows to functions to be bound to button events.
 *
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#pragma once
#include "Cerberus/Core/UI/CWidget.h"
#include <functional>

class CWidget_Button :
    public CWidget
{
public:

    CWidget_Button();
   

   /**
    * Sets the button text.
    * 
    * \param TextBody
    */
    void SetText(std::string TextBody);
    /**
     * Sets the button size, does not currently affect text.
     * 
     * \param Size
     */
    void SetButtonSize(Vector2 Size);
    /**
     * Sets the button texture.
     * 
     * \param filePath
     */
    void SetTexture(std::string filePath);
    
    /**
     * Sets the widget transform on screen. Overriden from CWidget.
     * 
     * \param Position Position on screen, relative to anchor
     * \param Anchor Anchor position on screen
     * \param ZOrder Z-Order
     */
    virtual void SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder);
    

    virtual void Update(float deltaTime) override;

    /**
     * On button Pressed event.
     * 
     */
    virtual void OnButtonPressed();
    virtual void OnButtonReleased();

    virtual void OnButtonHoverStart();
    virtual void OnButtonHoverEnd();


    virtual void SetVisibility(bool IsVisible);

    void IsButtonFocused(Vector2 mPos);
    void ButtonPressed(bool buttonPressed);

    /**
     * Binds a function to this button event.
     * 
     * \param functionToBind The function to be bound, to bind a function use std::bing(&ClassName::FunctionName, ObjectReference)
     */
    void Bind_OnButtonPressed(std::function<void()> functionToBind) { ButtonPressedBind = functionToBind; }
    /**
     * Binds a function to this button event.
     *
     * \param functionToBind The function to be bound, to bind a function use std::bing(&ClassName::FunctionName, ObjectReference)
     */
    void Bind_OnButtonReleased(std::function<void()> functionToBind) { ButtonReleasedBind = functionToBind; }
    /**
     * Binds a function to this button event.
     *
     * \param functionToBind The function to be bound, to bind a function use std::bing(&ClassName::FunctionName, ObjectReference)
     */
    void Bind_HoverStart(std::function<void()> functionToBind) { HoverStartBind = functionToBind; }
    /**
     * Binds a function to this button event.
     *
     * \param functionToBind The function to be bound, to bind a function use std::bing(&ClassName::FunctionName, ObjectReference)
     */
    void Bind_HoverEnd(std::function<void()> functionToBind) { ButtonReleasedBind = functionToBind; }

    class CSpriteComponent* GetSprite() { return sprite; }
    class CTextRenderComponent* GetText() { return textRenderer; }

    bool ButtonHasFocus() { return hasFocus; }


private: 

    Vector2 spriteSize;

    std::function<void()> HoverStartBind;
    std::function<void()> HoverEndBind;

    std::function<void()> ButtonPressedBind;
    std::function<void()> ButtonReleasedBind;

   
    int buttonSlot;
    bool hasFocus;

    bool ButtonHeld = false;
   
    class CWidget_Canvas* owningCanvas;

    class CSpriteComponent* sprite = nullptr;
    class CTextRenderComponent* textRenderer = nullptr;

    

    



};

