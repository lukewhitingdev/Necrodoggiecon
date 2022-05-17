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
    int charactersPerSecond = 4;
    float timer = 0;
    bool needsUpdate = false;


    std::string displayingText;
    std::string reserveText;
    void UpdateText();

public:
    DialogueUI();
    virtual ~DialogueUI();
    virtual void Update(float deltaTime) override;

    void SetText(std::string newText, bool instantDisplay);
    void ClearText();
};

