#pragma once
#include <Cerberus/Core/CEntity.h>
#include <Cerberus/Core/Components/CSpriteComponent.h>
#include <Cerberus/Core/Components/CTextRenderComponent.h>

class CAudioEmitterComponent;
/**
 * Class that handles displaying text in the dialogue window.
 */
class DialogueUI :  public CEntity
{
private:
    CSpriteComponent* textBackground;
    std::vector<CTextRenderComponent*> textRenderComponents;

    CSpriteComponent* nameBackground;
    CTextRenderComponent* nameTextRenderComponent;
    CAudioEmitterComponent* audioEmitterComponent;

    void UpdateTextComponentPosition(CTextRenderComponent* textComponent, int row);
    float GetUIHeight();

    float UIHeightPercent = 0.3f;
    int maxCharactersInRow;
    int maxRowCount;
    int rowPadding = 4;
    int rowHeight;
    int charactersPerSecond = 50;
    float timer = 0;
    bool isUpdating = false;


    std::string displayingText;
    std::string reserveText;
    std::string nameText;
    void UpdateText();
    int width = 0;
    int height = 0;
    void SetSize();

public:
    DialogueUI();
    virtual ~DialogueUI();
    virtual void Update(float deltaTime) override;

    void SetText(const std::string& newText, bool instantDisplay);
    void SetName(const std::string& newName);
    void ClearText();
    void Complete();
    void CompletePage();
    bool IsUpdating() { return isUpdating; }
    bool IsComplete();
    void Advance();
    void ToggleDrawing(bool shouldDraw);
    int GetReserveCharacterCount() { return reserveText.size(); }
};

