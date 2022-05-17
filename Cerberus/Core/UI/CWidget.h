#pragma once
#include "Cerberus/Core/CEntity.h"
class CWidget :
    public CEntity
{

    CWidget* GetParent();
    void SetParent(CWidget* NewParent);
    const std::vector<CWidget*> GetChildren() { return ChildWidgets; }






private: 

    CWidget* ParentWidget;
    std::vector<CWidget*> ChildWidgets;



};

