#pragma once
#include "Cerberus/Core/CEntity.h"
class CWidget :
    public CEntity
{
public:

    CWidget();

    virtual ~CWidget();

    CWidget* GetParent() { return parentWidget; }
   
    const std::vector<CWidget*> GetChildren() { return childWidgets; }


    virtual void SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder);

    virtual void SetVisibility(bool IsVisible);

    void AddChild(CWidget* NewChild);

    void RemoveAllChildren();


     void UpdateWidgetOrigin(Vector3 Pos);

private: 
    CWidget* parentWidget = nullptr;

    std::vector<CWidget*> childWidgets;

protected:
    bool WidgetIsVisible = true;

};

