#pragma once
#include <Cerberus/Core/CEntity.h>
#include <Cerberus/Core/Components/CSpriteComponent.h>
#include <Cerberus/Core/Components/CTextRenderComponent.h>

class DialogueUI :  public CEntity
{
private:
    CSpriteComponent* textBackground;
    std::vector<CTextRenderComponent*> textRenderComponents;

    CSpriteComponent* nameBackground;
    CTextRenderComponent* nameTextRenderComponent;


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
    std::string nameText;
    void UpdateText();

public:
    DialogueUI();
    virtual ~DialogueUI();
    virtual void Update(float deltaTime) override;

    void SetText(std::string newText, bool instantDisplay);
    void SetName(std::string newName);
    void ClearText();
};

