#include "DialogueUI.h"



DialogueUI::DialogueUI()
{
	spriteComponent = AddComponent<CSpriteComponent>();

	spriteComponent->LoadTextureWIC("Resources/darkBackground.png");

	//Setup Background Sprite
	auto width = Engine::windowWidth;
	auto height = Engine::windowHeight * UIHeightPercent;
	spriteComponent->SetRenderRect(XMUINT2(width, height));
	spriteComponent->SetSpriteSize(XMUINT2(width, height));
	spriteComponent->SetAnchor(XMFLOAT2(0, 1));
	float UIHeight = GetUIHeight();
	spriteComponent->SetPosition(0, UIHeight, 1);

	//Setup TextRenderComponents
	auto trc = AddComponent<CTextRenderComponent>();
	textRenderComponents.push_back(trc);

	maxCharactersInRow = width / textRenderComponents[0]->GetCharacterSize().x;
	rowHeight = textRenderComponents[0]->GetCharacterSize().y + rowPadding;
	maxRowCount = (height / rowHeight) * 0.5f;

	textRenderComponents.clear();
	for (int i = 0; i < maxRowCount; i++)
	{
		auto trc = AddComponent<CTextRenderComponent>();
		textRenderComponents.push_back(trc);
	}

	//textRenderComponents[0]->SetText("abc");
	//UpdateTextComponentPosition(textRenderComponents[0], 1);

	for (int i = 0; i < textRenderComponents.size(); i++)
	{
		textRenderComponents[i]->SetText("abc" + std::to_string(i));
		UpdateTextComponentPosition(textRenderComponents[i], i + 1);
	}

	Debug::Log(std::to_string(maxCharactersInRow).c_str());
	Debug::Log(std::to_string(maxRowCount).c_str());

	for (CComponent* e : components)
		e->ui = true;
}

void DialogueUI::UpdateTextComponentPosition(CTextRenderComponent* textComponent, int row)
{
	int charCount = textComponent->GetText().size();
	XMUINT2 charSize = textComponent->GetCharacterDrawSize();

	int xPos = -(Engine::windowWidth * 0.5f) + (charSize.x * 0.5f * (charCount + 1));
	int yPos = (GetUIHeight() * 0.5f) - charSize.y - (rowHeight * 2 * (row));
	textComponent->SetPosition(xPos, yPos, 0);
}

float DialogueUI::GetUIHeight()
{
	float height = Engine::windowHeight * UIHeightPercent;
	return -(Engine::windowHeight * 0.5f) + (height * 0.5f);
}

DialogueUI::~DialogueUI()
{
}

void DialogueUI::Update(float deltaTime)
{
}
