#pragma once
#include <Cerberus/Core/CEntity.h>
#include <Cerberus/Core/Components/CSpriteComponent.h>
#include <Cerberus/Core/Components/CTextRenderComponent.h>

class DialogueUI :  public CEntity
{
private:
    CSpriteComponent* spriteComponent;
    std::vector<CTextRenderComponent*> textRenderComponents;


    void UpdateTextComponentPosition(CTextRenderComponent* textComponent, int row);
    float GetUIHeight();

    float UIHeightPercent = 0.3f;
    int maxCharactersInRow;
    int maxRowCount;
    int rowPadding = 4;
    int rowHeight;
public:
    DialogueUI();
    virtual ~DialogueUI();
    virtual void Update(float deltaTime) override;
};

