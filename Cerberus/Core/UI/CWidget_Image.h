/*****************************************************************//**
 * \file   CWidget_Image.h
 * \brief  Image widget class. 
 * 
 * \author J019857i
 * \date   May 2022
 *********************************************************************/
#pragma once
#include "Cerberus/Core/UI/CWidget.h"
class CWidget_Image :
    public CWidget
{


public:
    CWidget_Image();

  
   

    virtual void Update(float deltaTime) override;

    /**
     * Sets widget transform on screen. Overriden from parent.
     * 
     * \param Position
     * \param Anchor
     * \param ZOrder
     */
    virtual void SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder);

    class CSpriteComponent* GetSprite() { return sprite; }
    class CTextRenderComponent* GetText() { return textRenderer; }

    void SetSpriteData(Vector2 SpriteSize, std::string filePath);

    virtual void SetVisibility(bool IsVisible);

protected: 

    class CSpriteComponent* sprite = nullptr;

    class CTextRenderComponent* textRenderer = nullptr;


};

