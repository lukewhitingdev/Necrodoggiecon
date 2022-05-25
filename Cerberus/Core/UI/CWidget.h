#pragma once
#include "Cerberus/Core/CEntity.h"
class CWidget :
    public CEntity
{
public:

    CWidget();

    CWidget* GetParent() { return parentWidget; }
   
    const std::vector<CWidget*> GetChildren() { return childWidgets; }


    virtual void SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder);

    virtual void SetVisibility(bool IsVisible);

    void AddChild(CWidget* NewChild);

    void RemoveAllChildren();

private: 
    CWidget* parentWidget;

    std::vector<CWidget*> childWidgets;

};

