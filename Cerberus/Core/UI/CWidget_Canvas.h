/*****************************************************************//**
 * \file   CWidget_Canvas.h
 * \brief  Main container for all widget classes. If a widget is being used it should be instantiated through this object first. This enables easy access and tidy management.
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#pragma once
#include "Cerberus/Core/UI/CWidget.h"
#include <functional>
class CWidget_Canvas :
    public CWidget
{


public:

    CWidget_Canvas();

 
    /**
     * Initialises the canvas. Instantiate all widgets inside this function
     * 
     */
    virtual void InitialiseCanvas();

    virtual void Update(float deltaTime) override;

    /**
     * Gett position of the mouse on screen.
     * 
     * \return 
     */
    Vector2 GetMousePosition();

   
    /**
     * Creates a Button Widget inside the canvas.
     */
    class CWidget_Button* CreateButton(Vector2 Position, Vector2 Anchor, std::string& ButtonName, int ZOrder);
    /**
     * Creates an Image Widget inside the canvas.
     */
    class CWidget_Image* CreateImage(Vector2 Position, Vector2 Anchor, int ZOrder);
    /**
     * Creates a Text Widget inside the canvas.
     */
    class CWidget_Text* CreateText(Vector2 Position, Vector2 Anchor, int ZOrder, std::string& Text);

   
    /**
     * Sets the visibility of this canvas and all children.
     * 
     * \param IsVisible
     */
    virtual void SetVisibility(bool IsVisible);




protected: 

    /**
     * List of all buttons istantiated by this canvas, used to activate their events when required.
     */
    std::vector<class CWidget_Button*> buttonList;
    
    
};

